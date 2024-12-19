from cryptography.hazmat.backends import default_backend
from cryptography.hazmat.primitives.asymmetric import dsa
from cryptography.hazmat.primitives import serialization
from cryptography.hazmat.primitives import hashes

def generate_keys():
    # Generate a DSA private key
    private_key = dsa.generate_private_key(key_size=2048, backend=default_backend())
    public_key = private_key.public_key()

    # Serialize keys to save them for later use
    private_pem = private_key.private_bytes(
        encoding=serialization.Encoding.PEM,
        format=serialization.PrivateFormat.TraditionalOpenSSL,
        encryption_algorithm=serialization.NoEncryption()  # No encryption
    )
    public_pem = public_key.public_bytes(
        encoding=serialization.Encoding.PEM,
        format=serialization.PublicFormat.SubjectPublicKeyInfo
    )

    return private_pem, public_pem

def sign_message(private_key_pem, message):
    # Load the private key from PEM format (add password=None)
    private_key = serialization.load_pem_private_key(
        private_key_pem, 
        password=None,  # Specify None for unencrypted key
        backend=default_backend()
    )

    # Create a signature for the message
    signature = private_key.sign(
        message.encode(),
        hashes.SHA256()  # Hashing algorithm
    )
    return signature

def verify_signature(public_key_pem, message, signature):
    # Load the public key from PEM format
    public_key = serialization.load_pem_public_key(public_key_pem, backend=default_backend())

    # Verify the signature
    try:
        public_key.verify(
            signature,
            message.encode(),
            hashes.SHA256()  # Hashing algorithm
        )
        return True  # Signature is valid
    except Exception:
        return False  # Signature is invalid

def main():
    # Generate keys
    private_key, public_key = generate_keys()

    # Input message to sign
    message = input("Enter the message to sign: ")

    # Sign the message
    signature = sign_message(private_key, message)
    print("Signature:", signature.hex())

    # Verify the signature
    is_valid = verify_signature(public_key, message, signature)
    print("Is the signature valid?", is_valid)

if __name__ == "__main__":
    main()
