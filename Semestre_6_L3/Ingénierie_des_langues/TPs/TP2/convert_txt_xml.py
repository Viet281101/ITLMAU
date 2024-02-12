
import re
from xml.etree.ElementTree import Element, SubElement, tostring
from xml.dom.minidom import parseString


def convert_txt_xml(input_file_path, output_file_path) -> None:
	""" Converts a text file to an xml file """

	### Read input
	with open(input_file_path, 'r', encoding='utf-8') as file:
		content = file.read()

	### Using regex to split text
	sentences = re.split(r'(?<=[.!?]) +', content)

	### Find xml path
	root = Element('text')
	for i, sentence in enumerate(sentences):
		sentence_element = SubElement(root, 'sentence', id=str(i))
		sentence_element.text = sentence.strip()

	### convert xml to string
	xml_str = parseString(tostring(root, 'utf-8')).toprettyxml(indent="    ")

	### write into xml file
	with open(output_file_path, 'w', encoding='utf-8') as xml_file:
		xml_file.write(xml_str)


if __name__ == "__main__":
	input_file_path = 'conte.txt'
	output_file_path = 'output.xml'
	convert_txt_xml(input_file_path, output_file_path)

