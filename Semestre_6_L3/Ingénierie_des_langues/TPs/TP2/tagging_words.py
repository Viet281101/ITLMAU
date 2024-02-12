
import spacy

nlp = spacy.load("fr_core_news_sm")

def tag_words(input_file_path, output_file_path):
    """ Tag the words of the input file using spacy """

    ### Read input
    with open(input_file_path, 'r', encoding='utf-8') as input_file:
        text = input_file.read()

    doc = nlp(text)

    ### Write output
    with open(output_file_path, 'w', encoding='utf-8') as output_file:
        for token in doc:
            output_file.write(f"{token.text},{token.pos_}\n")

if __name__ == "__main__":
    input_file_path = 'output/words_output.txt'
    output_file_path = 'output/tagged_words_output.csv'
    tag_words(input_file_path, output_file_path)
