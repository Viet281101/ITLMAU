
from lxml import etree

def transform(xml_path, xslt_path):
    # Parse XML and XSLT files
    xml = etree.parse(xml_path)
    xslt = etree.parse(xslt_path)

    # Create a transform function
    transform = etree.XSLT(xslt)

    # Apply the transformation
    result = transform(xml)

    # Write the result to an HTML file
    with open('output.html', 'w') as f:
        f.write(str(result))


### Call the function with paths to your files
# transform('input.xml', 'transform.xslt')

def main():
    transform('magic_circle.xml', 'magic_circle.xsl')


if __name__ == '__main__':
    main()
