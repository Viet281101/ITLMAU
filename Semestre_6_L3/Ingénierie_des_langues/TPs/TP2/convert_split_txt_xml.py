
import spacy
import xml.etree.ElementTree as ET


nlp = spacy.load("fr_core_news_sm")

def text_to_xml(input_file_path, output_file_path):
	""" Convert the input text file to an xml file """	

	with open(input_file_path, 'r', encoding='utf-8') as file:
		text = file.read()

	doc = nlp(text)

	root = ET.Element('text')

	for i, sent in enumerate(doc.sents):
		sentence_element = ET.SubElement(root, 'sentence', id=str(i))
		for token in sent:
			word_element = ET.SubElement(sentence_element, 'mot')
			word_element.text = token.text

	tree = ET.ElementTree(root)
	tree.write(output_file_path, encoding='utf-8', xml_declaration=True)


if __name__ == "__main__":
	input_file_path = 'conte.txt'  
	output_file_path = 'output/conte_output_2.xml'  
	text_to_xml(input_file_path, output_file_path)

