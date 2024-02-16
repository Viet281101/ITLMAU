
from sklearn.feature_extraction.text import CountVectorizer
import glob

import re

texts = {"appr":[], "test":[]}
classes= {"appr":[], "test":[]}

for path in glob.glob("corpus_multi/*/*/*")[:1500]:
	_, lg, corpus, filename = re.split("/", path)
	classes[corpus].append(lg)
	with open(path, encoding="utf−8") as f:
		fstring = f.read()
		texts[corpus].append(fstring)


vectorizer = CountVectorizer()
X = vectorizer.fit_transform(texts["appr"])
print(vectorizer.get_feature_names_out())
print(X.toarray())
print(X.shape)
print(classes["appr"])
print(len(classes["appr"]))


