
import numpy as np
import matplotlib.pyplot as plt

### Read CSV files
def read_csv(file_path):
	data = []
	with open(file_path, "r") as file:
		for line in file:
			stripped_line = line.strip().rstrip(';')
			data.append(stripped_line.split(";"))
	return np.array(data, dtype=np.float32)





def main():
	data_path = "iris/iris_data.csv"
	data = read_csv(data_path)

	label_path = "iris/iris_label.csv"
	labels = read_csv(label_path)


if __name__ == "__main__":
	main()

