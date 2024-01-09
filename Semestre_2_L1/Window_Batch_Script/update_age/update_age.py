
import xml.etree.ElementTree as ET

xml_file = 'ex_info.xml'

tree = ET.parse(xml_file)
root = tree.getroot()

age_element = root.find('age')
if age_element is not None:
    age = int(age_element.text)
    age_element.text = str(age + 1)
    tree.write(xml_file)
    print(f"Age updated: {age + 1}")
else:
    print("Age element not found in XML.")

