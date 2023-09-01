# Counting queries
def updateMinedWord(queries, dict):
  for wrd in queries:
    if wrd in dict:
      dict[wrd] += 1
    else:
      dict[wrd] = 1

# Mining from a text file
def mineFromTXT(path, query):
  kw = {}
  f = open(path)
  txt = f.read()
  updateMinedWord(re.findall(query, txt), kw)
  return kw

# Mining from a PDF file
def mineFromPDF(path, query):
  (name,ext) = os.path.splitext(path)
  tmp = name+'.extract.txt'
  manager = PDFResourceManager()
  with open(tmp, "wb") as output:
    with open(path, 'rb') as input:
      with TextConverter(manager, output, codec='utf-8', laparams=LAParams()) as conv:
        interpreter = PDFPageInterpreter(manager, conv)
        for page in PDFPage.get_pages(input):
          interpreter.process_page(page)
  return mineFromTXT(tmp, query)

# Mining from a Word file(.docx)
def mineFromDOC(path, query):
  kw = {}
  doc = docx.Document(path)
  for para in doc.paragraphs:
    updateMinedWord(re.findall(query, para.text), kw)
  return kw

# Mining from a Excel file(.xlsx)
def mineFromXLS(path, query):
  kw = {}
  workbook = openpyxl.load_workbook(path)
  for ws in workbook.worksheets:
    for row in ws.iter_rows():
      for cell in row:
        if cell.value:
          updateMinedWord(re.findall(query, str(cell.value)), kw)
  return kw

# Mining from an archive file (.tar.gz)
def mineFromArchive(path, query):
  os.system('tar -xvzf '+ path)
  dir = path.replace('.tar.gz', '')
  return mineWordFrom(dir, query)

# Mining keywords
def mineWord(path, query):
  if path.endswith('.htm') or path.endswith('.xml'):
    return mineFromTXT(path, query)
  elif path.endswith('.pdf'):
    return mineFromPDF(path, query)
  elif path.endswith('.docx'):
    return mineFromDOC(path, query)
  elif path.endswith('.xlsx'):
    return mineFromXLS(path, query)
  elif path.endswith('.gz'):
    return mineFromArchive(path, query)
  else:
    print('Unkown file:', path)
    return {}

def mineWordFrom(dir, query):
  kw = {}
  files = os.listdir(dir)
  for f in files:
    file = os.path.join(dir, f)
    if os.path.isfile(file):
      mining = mineWord(file, query)
      updateMinedWord(mining, kw)
    elif os.path.isdir(file):
      mining = mineWordFrom(file, query)
      updateMinedWord(mining, kw)
  return kw
