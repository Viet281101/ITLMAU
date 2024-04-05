
import json

def json_to_dict(filename):
	with open(filename, 'r', encoding='utf-8') as file:
		data = json.load(file)
		movie_dict = { item['Title']: item['Plot'] for item in data }
	return movie_dict


movie_dict = json_to_dict('films.json')
# print(movie_dict)


import nltk
from nltk.corpus import stopwords
from nltk.tokenize import word_tokenize
from nltk.stem import WordNetLemmatizer

# nltk.download('punkt')
# nltk.download('stopwords')
# nltk.download('wordnet')

def nlp(sentence):
	tokens = word_tokenize(sentence)

	tokens = [word for word in tokens if word.isalpha() and word not in stopwords.words('english')]

	lemmatizer = WordNetLemmatizer()
	tokens = [lemmatizer.lemmatize(word) for word in tokens]
	return tokens

sentence = "Two imprisoned men bond over a number of years, finding solace and eventual redemption through acts of common decency"
tokens = nlp(sentence)
# print(tokens)



def nlp_dico(movie_dict):
	processed_dict = {}
	for title, plot in movie_dict.items():
		processed_dict[title] = nlp(plot)
	return processed_dict

processed_movies = nlp_dico(movie_dict)
# print(processed_movies['The Shawshank Redemption'])



def jaccard_similarity(list1, list2):
	set1, set2 = set(list1), set(list2)
	intersection = len(set1.intersection(set2))
	union = len(set1.union(set2))
	return intersection / union if union != 0 else 0

similarity_score = jaccard_similarity(processed_movies['The Shawshank Redemption'], processed_movies['The Godfather'])
print(similarity_score)



def jaccard_similarity_from_title(title1, title2, processed_movies):
	tokens1 = processed_movies.get(title1, [])
	tokens2 = processed_movies.get(title2, [])
	similarity_score = jaccard_similarity(tokens1, tokens2)
	print(f"Jaccard similarity between '{title1}' and '{title2}' is: {similarity_score}")
	return similarity_score

jaccard_similarity_from_title('The Shawshank Redemption', 'The Godfather', processed_movies)

