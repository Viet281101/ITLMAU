
from lxml import etree

def transform(xml_path, xslt_path, output:str):
	# Parse XML and XSLT files
	xml = etree.parse(xml_path)
	xslt = etree.parse(xslt_path)

	# Create a transform function
	transform = etree.XSLT(xslt)

	# Apply the transformation
	result = transform(xml)

	# Write the result to an HTML file
	with open(output, 'w') as f:
		f.write(str(result))


### Call the function with paths to your files
# transform('input.xml', 'transform.xslt')

def main():
	transform('output.xml', 'output.xsl', 'output.html')
	transform('conte_output.xml', 'output.xsl', 'conte_output.html')
	transform('conte_output_2.xml', 'conte_output_2.xsl', 'conte_output_2.html')
	transform('tagged_words_output.xml', 'tagged_words_output.xsl', 'tagged_output.html')


if __name__ == '__main__':
	main()
