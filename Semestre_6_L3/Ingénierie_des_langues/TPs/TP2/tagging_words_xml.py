
import spacy
import xml.etree.ElementTree as ET

nlp = spacy.load("fr_core_news_sm")

def tag_words_to_xml(input_file_path, output_file_path):
	""" Tag the words of the input file using spacy and output to XML """

	### Read input
	with open(input_file_path, 'r', encoding='utf-8') as input_file:
		text = input_file.read()

	doc = nlp(text)

	### Create the root element
	root = ET.Element('text')

	### Process each token in the document
	for token in doc:
		### Create 'word' element for each token
		word_element = ET.SubElement(root, 'mot', categorie=token.pos_)
		word_element.text = token.text

	### Generate the tree and write to an XML file
	tree = ET.ElementTree(root)
	tree.write(output_file_path, encoding='utf-8', xml_declaration=True)

if __name__ == "__main__":
	input_file_path = 'output/words_output.txt'
	output_file_path = 'output/tagged_words_output.xml'
	tag_words_to_xml(input_file_path, output_file_path)

