#include "sobj.h"
#include "sbioinfo.h"
using namespace slib;
using namespace slib::sbio;
int main(int argc, const char** argv) {
	sbio::SBSeqList reference;
	sbio::SBAnnotDB annotdb;
	sbio::SVarList vl, control;
	sbio::svariant_param param;
	sio::SFile input, output;
	Array<intarray> histdata;
	String format, outdir, ref;
	bool ems = false, enu = false, hist = false;
	int hbin = 0;
	int required = 0;

	sforin(i, 0, argc) {
		String op(*argv);
		if (op == "--reference") {
			++i; ++argv;
			reference.load(*argv);
			required |= 0x01;
		}
		else if (op == "--annotdb") {
			++i; ++argv;
			annotdb.open(*argv);
			annotdb.load(sbio::SBAnnotDB::LOAD_GENE | sbio::SBAnnotDB::LOAD_TRANS | sbio::SBAnnotDB::LOAD_MUT);
			required |= 0x02;
		}
		else if (op == "--input") {
			++i; ++argv;
			input.open(*argv);
		}
		else if (op == "--vcontrol") {
			++i; ++argv;
			sio::SFile vc(*argv, sio::READ);
			String ln;
			while (!vc.eof()) {
				vc.readLine(ln);
				if (ln.empty()) continue;
				auto values = ln.split(TAB);
				sbio::SVariant var;
				var.ref[0] = values[0];
				var.pos[0].idx = reference.index[var.ref[0]];
				var.pos[0].begin = values[1].intValue();
				var.pos[0].end = values[2].intValue();
				var.alt = values[3];
				var.type = values[4].intValue();
				control.add(var);
			}
			required |= 0x04;
		}
		else if (op == "--homo_only") {
			param.homo_select = true;
		}
		else if (op == "--filter") {
			++i; ++argv;
			String tmp(*argv);
			if (tmp == "ems") ems = true;
			else if (tmp == "enu") enu = true;
		}
		else if (op == "--export-hist") {
			hist = true;
			++i; ++argv;
			String tmp(*argv);
			if (tmp[tmp.size() - 1] == 'K') {
				hbin = (int)(tmp.substring(0, tmp.size() - 1).doubleValue() * 1000.0);
			}
			else if (tmp[tmp.size() - 1] == 'M') {
				hbin = (int)(tmp.substring(0, tmp.size() - 1).doubleValue() * 1000000.0);
			}
			else hbin = tmp.intValue();
		}
		else if (op == "--oformat") {
			++i; ++argv;
			format = *argv;
		}
		else if (op == "--outdir") {
			++i; ++argv;
			outdir = *argv;
		}
		++argv;
	}
	if (hist) {
		histdata.resize(reference.size());
		sforeachi(reference) {
			histdata[i].resize((reference[i]->length() - 1) / hbin + 1);
		}
	}
	sbio::SVarFilter filter(&reference, &annotdb, &param);
	sbio::SVarIO::loadVCF(input, &vl, &reference, nullptr);
	filter.subtract(vl, control);
	sforeach(vl) {
		try {
			auto advals = E_->attribute["AD"].string().split(",");
			E_->attribute["AD"] = advals[advals.size() - 1];
			E_->copy.frequency = E_->attribute["AD"].doubleValue() / E_->attribute["DP"].doubleValue();
			if (E_->copy.frequency > 0.75) E_->homo = true;
			else E_->homo = false;
			if (param.homo_select && !E_->homo) E_->flag |= sbio::UNAVAILABLE_FLAG;
			if (ems) {
				if (E_->type == sbio::SNV) {
					ref = reference[E_->pos[0].idx]->raw(E_->pos[0].begin - 1, 1);
					if ((ref == "G" && E_->alt == "A") || (ref == "C" && E_->alt == "T")) {}
					else E_->flag |= sbio::UNAVAILABLE_FLAG;
				}
				else E_->flag |= sbio::UNAVAILABLE_FLAG;
			}
			if (enu) {
				if (E_->type == sbio::SNV) {
					ref = reference[E_->pos[0].idx]->raw(E_->pos[0].begin - 1, 1);
					if ((ref == "A" && (E_->alt == "T" || E_->alt == "G")) || (ref == "T" && (E_->alt == "A" || E_->alt == "C")) ||
						(ref == "G" && E_->alt == "A") || (ref == "C" && E_->alt == "T")) {
					}
					else E_->flag |= sbio::UNAVAILABLE_FLAG;
				}
				else E_->flag |= sbio::UNAVAILABLE_FLAG;
			}
		}
		catch (SException ex) {
			ex.print();
			SPrint(E_->ref[0],":", E_->pos[0].begin);

		}
	}
	vl.tidy();
	filter.annotate(&vl);
	output.make(outdir + PATH_SEPARATOR + vl.name + "." + format);
	if (format == "tsv") {
		output << "Chr" << TAB <<
			"Pos" << TAB <<
			"Length" << TAB <<
			"Alt/Ins" << TAB <<
			"Type" << TAB <<
			"Genotype" << TAB <<
			"Gene" << TAB <<
			"Region" << TAB <<
			"Mutation" << TAB <<
			"Substitution" << TAB <<
			"Mutant" << TAB <<
			"Coverage" << TAB <<
			"Allele coverage" << TAB <<
			"Frequency" << TAB <<
			"Quality" << TAB <<
			"Evaluation" << NEW_LINE;
		sforeach(vl) {
			try {
				output << E_->ref[0] << TAB << E_->pos[0].begin << TAB;
				if (E_->type & DELETION || E_->type == INVERSION || E_->type == DUPLICATION || E_->type == MULTIPLICATION) output << E_->pos[0].length(true) << TAB;
				else if (E_->type == SNV || E_->type == MNV || E_->type == INSERTION) output << E_->alt.length() << TAB;
				else output << "0" << TAB;
				output << E_->alt << TAB;
				output << (E_->homo ? "Homo" : "Hetero") << TAB;
				if (!E_->genes.empty()) {
					stringarray gnames;
					auto count = 0;
					sforeach_(git, E_->genes) {
						if (count == 5) break;
						gnames.add(git->name); ++count;
					}
					output << slib::toString(gnames) << (E_->genes.size() > 5 ? " etc..." : "") << TAB;
				}
				else output << "-" << TAB;
				if (!E_->genes.empty()) {
					stringarray regions;
					auto count = 0;
					sforeach_(git, E_->genes) {
						if (count == 5) break;
						auto sites = sbiutil::geneSite(git->annotatedSite());
						regions.add(sites.empty() ? "-" : sites[0]);
						++count;
					}
					output << slib::toString(regions) << (E_->genes.size() > 5 ? " etc,,," : "") << TAB;
				}
				else output << "-" << TAB;
				if (!E_->genes.empty()) {
					stringarray mnames;
					auto count = 0;
					sforeach_(git, E_->genes) {
						if (count == 5) break;
						auto muts = sbiutil::mutType(git->mutation);
						mnames.add(muts.empty() ? "-" : muts[0]);
						++count;
					}
					output << slib::toString(mnames) << (E_->genes.size() > 5 ? " etc,,," : "") << TAB;
				}
				else output << "-" << TAB;
				if (!E_->genes.empty()) {
					stringarray subs;
					auto count = 0;
					sforeach_(git, E_->genes) {
						if (count == 5) break;
						if (git->transcripts.empty()) subs.add("No transcript");
						else {
							String sub;
							sforeach_(tit, git->transcripts) {
								if (tit->site & sbio::CDS && 0 < tit->pos) sub << tit->name << ":" << tit->ori << tit->pos << tit->alt << ";";
							}
							subs.add(sub);
						}
						++count;
					}
					output << slib::toString(subs) << (E_->genes.size() > 5 ? " etc,,," : "") << TAB;
				}
				else output << "-" << TAB;
				if (!E_->mutants.empty()) {
					output << (E_->mutants.size() > 10 ? slib::toString(E_->mutants.subarray(0, 10)) : slib::toString(E_->mutants)) << TAB;
				}
				else output << "-" << TAB;
				output << E_->attribute["DP"].intValue() << TAB << E_->attribute["AD"].intValue() << TAB <<
					E_->copy.frequency << TAB << E_->qual << TAB;
				if (E_->attribute.hasKey("SIFTINFO")) {
					auto vals = E_->attribute["SIFTINFO"].string().split("|");
					output << vals[12] << "(" << vals[8].floatValue() << ")";
				}
				else output << "-";
				output << NEW_LINE;
				output.flush();
				if (hist) {
					++histdata[E_->pos[0].idx][E_->pos[0].begin / hbin];
				}
			}
			catch (SException ex) { ex.print(); }
		}
		output.close();
		if (hist) {
			SArray harray;
			sforeachi(histdata) {
				sforeachi_(j, histdata[i]) {
					harray.add(SDictionary({
						kv("block_id", reference[i]->name),
						kv("start", j * hbin),
						kv("end", j * hbin + hbin - 1),
						kv("value", histdata[i][j])
						}));
				}
			}
			SJson js(harray);
			js.save(outdir + PATH_SEPARATOR + vl.name + ".hist.json");
		}
	}
	return 0;
}
