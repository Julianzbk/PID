import matplotlib.pyplot as plt

if __name__ == "__main__":
    file = open("data.txt")
    header = file.readline().strip('\n')
    target = float(file.readline().strip('\n'))
    lines = [float(num.strip('\n')) for num in file.readlines()[1:]]
    ys = lines
    xs = [x for x in range(len(ys))]
    print(header, lines)
    plt.plot(xs, ys)
    plt.title(header)
    plt.axhline(y = 15, color = 'r', linestyle = '-')
    plt.savefig(f"graphs/{header}_target={target}.png")
    plt.show()
    plt.close()