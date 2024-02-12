
import xml.etree.ElementTree as ET
import spacy

nlp = spacy.load("fr_core_news_sm")

def split_sentences_to_words(xml_file_path, output_file_path):
	""" Split the sentences of the XML file to words using spacy """

	### Read the XML file
	tree = ET.parse(xml_file_path)
	root = tree.getroot()

	with open(output_file_path, 'w', encoding='utf-8') as output_file:
		for sentence in root.findall('.//sentence'):
			text = sentence.text
			doc = nlp(text)
			words = [token.text for token in doc]
			output_file.write(f"Sentence ID: {sentence.get('id')} - Words: {words}\n")


if __name__ == "__main__":
	xml_file_path = "output/output.xml"
	output_file_path = 'output/words_output.txt'
	split_sentences_to_words(xml_file_path, output_file_path)
