import hashlib

def main():
    # Input text
    message = input("Enter the message: ")

    # Step 1: Create a SHA-1 hash object
    sha1 = hashlib.sha1()

    # Step 2: Update the hash object with the bytes of the message
    sha1.update(message.encode('utf-8'))

    # Step 3: Calculate the hash digest in hexadecimal format
    digest = sha1.hexdigest()

    # Step 4: Output the message digest (in hexadecimal)
    print("SHA-1 Digest:", digest)

if __name__ == "__main__":
    main()
