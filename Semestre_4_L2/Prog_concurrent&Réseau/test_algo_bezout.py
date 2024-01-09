


def bezout(a:int, b:int) -> list:
    x : int = 1
    y : int = 0
    u : int = 0
    v : int = 1
    while b != 0:
        q : int = a // b
        r : int = a % b
        m : int = x - u * q
        n : int = y - v * q
        a = b
        b = r
        x = u
        y = v
        u = m
        v = n
    return [a, x, y]



def main() -> None:
    print(bezout(1686, 936))
    print(bezout(401, 130))


if __name__ == '__main__':
    main()


