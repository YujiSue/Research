# Get deteailed information for a specific PubMed ID
def getSummaryFromPM(refid, api_key):
  ref = {
      'id' : refid,
      'title': '',
      'author': [],
      'journal': '',
      'type' : '',
      'volume' : '',
      'issue' : '',
      'page' : '',
      'date' : '',
      'doi': '',
      'link': [],
      'file': '',
      'attribute' : {},
      'note': ''
      }
  entrez_que = 'https://eutils.ncbi.nlm.nih.gov/entrez/eutils/esummary.fcgi?db=pubmed&retmode=json&'
  entrez_que += 'id='+str(refid)+'&'
  entrez_que += 'api_key='+api_key+'&'
  response = requests.get(entrez_que)
  res = response.json()
  if 'result' in res:
    sum = res['result'][str(refid)]
    ref['title'] = sum['title']
    ref['title'] = ref['title'].replace('&lt;i&gt;', '')
    ref['title'] = ref['title'].replace('&lt;/i&gt;', '')
    ref['title'] = ref['title'].replace('&lt;sub&gt;', '')
    ref['title'] = ref['title'].replace('&lt;/sub&gt;', '')
    ref['title'] = ref['title'].replace('&lt;sup&gt;', '')
    ref['title'] = ref['title'].replace('&lt;/sup&gt;', '')
    for author in sum['authors']:
      ref['author'].append(author['name'])
    ref['journal'] = sum['fulljournalname']
    ref['type'] = ' '.join(sum['pubtype'])
    ref['volume'] = sum['volume']
    ref['issue'] = sum['issue']
    ref['page'] = sum['pages']
    ref['date'] = sum['pubdate']
    ref['doi'] = sum['elocationid']
  return ref

# Get PubMed ID list 
def getListFromPM(query, period, api_key):
  # Container to store results
  reflist = {}
  # URL generation
  entrez_que = 'https://eutils.ncbi.nlm.nih.gov/entrez/eutils/esearch.fcgi?'
  entrez_que += 'api_key='+api_key+'&'
  entrez_que += 'term='+query+'&'
  entrez_que += 'mindate='+period[0]+'&'
  entrez_que += 'maxdate='+period[1]+'&'
  entrez_que += 'retmode=json'
  # Total count of search results
  response = requests.get(entrez_que+'&rettype=count')
  res = response.json()
  total = response.json()['esearchresult']['count']
  if (0 < int(total)):
    # Request PubMed IDs
    response = requests.get(entrez_que+'&retmax='+str(total))
    refids = response.json()['esearchresult']['idlist']
    for refid in refids:
      # Get information of each ID
      reflist[str(refid)] = getSummaryFromPM(refid, api_key)
      time.sleep(0.25)
  return reflist

# Get abstract text from PubMed
def fetch_article_info(pmid):
    base_url = "https://eutils.ncbi.nlm.nih.gov/entrez/eutils/efetch.fcgi"
    params = {
        "db": "pubmed",
        "id": pmid,
        "retmode": "xml",
        "rettype": "abstract"
    }
    response = requests.get(base_url, params=params)
    xml_data = response.text
    # Parse the XML response to extract the abstract
    soup = BeautifulSoup(xml_data, "xml")
    abstract_element = soup.find("AbstractText")
    if abstract_element is not None:
        return abstract_element.text.strip()
    else:
        return None

# Redirect
def checkRedirect(url):
  response = requests.get(url)
  if (response.headers.get('Link') != None):
    beg = response.headers['Link'].find('http')
    end = response.headers['Link'].find('>', beg+1)
    if (end != -1):
      return response.headers['Link'][beg:end]
    else:
      return response.headers['Link']
  else:
    return url

# Elsevier
def elsevierLink(doi):
  response = requests.get('https://api.elsevier.com/content/object/doi/'+doi+'?httpAccept=application/json')
  return response.json()['attachment-metadata-response']['coredata']['link'][1]['@href']

# Conversion PubMedID => PMC ID
def getPMCID(refid):
  response = requests.get('https://www.ncbi.nlm.nih.gov/pmc/utils/idconv/v1.0/?tool=my_tool&email=my_email@example.com&ids='+refid+'&format=json')
  return response.json()['records'][0]['pmcid']

# Conversion PMC HTTPS URL => FTP URL
def pmcLink(pmcid):
  response = requests.get('https://www.ncbi.nlm.nih.gov/pmc/utils/oa/oa.fcgi?id='+pmcid)
  soup = BeautifulSoup(response.content, "xml")
  return soup.find(format="tgz")['href']

