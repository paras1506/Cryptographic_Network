from Crypto.Cipher import DES
from Crypto.Util.Padding import pad, unpad

def des_encrypt(plain_text, key):
    """Encrypt the plain text using DES algorithm, displaying intermediate steps.
    
    Parameters:
    plain_text (str): The text to be encrypted.
    key (bytes): The encryption key (must be 8 bytes long).
    
    Returns:
    bytes: The encrypted cipher text.
    """
    print("\nStarting encryption process...")

    # Create a DES cipher object
    cipher = DES.new(key, DES.MODE_ECB)
    print(f"Cipher initialized with key: {key.decode()} (in bytes: {key})")

    # Padding the plain text to make its size a multiple of the block size
    padded_text = pad(plain_text.encode(), DES.block_size)
    print(f"Padded plain text (in bytes): {padded_text}")

    # Encryption process
    encrypted_text = b''
    block_size = DES.block_size
    num_blocks = len(padded_text) // block_size

    for i in range(num_blocks):
        block = padded_text[i * block_size:(i + 1) * block_size]
        print(f"\nBlock {i + 1}: {block}")

        # Simulate processing the block in rounds (this is just for display purposes)
        intermediate = block
        for round_num in range(1, 17):  # DES has 16 rounds
            # This is a placeholder for round operations
            # Actual DES rounds involve Feistel functions, key mixing, etc.
            intermediate = cipher.encrypt(intermediate)
            print(f"After round {round_num}, intermediate (hex): {intermediate.hex()}")

        encrypted_text += intermediate

    print(f"\nFinal encrypted text (in bytes): {encrypted_text}")
    return encrypted_text

def des_decrypt(cipher_text, key):
    """Decrypt the cipher text using DES algorithm.
    
    Parameters:
    cipher_text (bytes): The encrypted text to be decrypted.
    key (bytes): The decryption key (must be 8 bytes long).
    
    Returns:
    str: The decrypted plain text.
    """
    print("\nStarting decryption process...")
    cipher = DES.new(key, DES.MODE_ECB)
    print(f"Cipher initialized with key: {key.decode()} (in bytes: {key})")

    # Decrypt the ciphertext
    decrypted_data = cipher.decrypt(cipher_text)
    print(f"Decrypted data (before unpadding, in bytes): {decrypted_data}")

    # Unpad the decrypted data
    try:
        decrypted_text = unpad(decrypted_data, DES.block_size)
    except ValueError as e:
        print(f"Error during unpadding: {e}")
        return None
    
    print(f"Decrypted text (in bytes): {decrypted_text}")
    return decrypted_text.decode()


def main():
    print("\nDES Encryption and Decryption")

    # Input encryption key from user
    key_input = input("Enter a key (8 bytes long, e.g., 'abcdefgh'): ")
    
    # Ensure the key is exactly 8 bytes long
    if len(key_input) != 8:
        print("Error: Key must be exactly 8 bytes long.")
        return

    key = key_input.encode()  # Convert to bytes
    print(f"Key used for encryption/decryption: '{key.decode()}' (in bytes: {key})")

    # Input plaintext
    plain_text = input("Enter the plain text to encrypt: ")
    print(f"Plain text: {plain_text}")

    # Encrypt the plaintext
    encrypted_text = des_encrypt(plain_text, key)
    print(f"\nEncrypted Text (in hexadecimal): {encrypted_text.hex()}") 
    print(f"Encrypted Text (in bytes): {encrypted_text}")

    # Decrypt the ciphertext
    decrypted_text = des_decrypt(encrypted_text, key)
    print(f"\nDecrypted Text: {decrypted_text}")

if __name__ == "__main__":
    main()
