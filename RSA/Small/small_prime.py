import math


def is_prime(num):
    if num < 2:
        return False
    for i in range(2, int(math.sqrt(num)) + 1):
        if num % i == 0:
            return False
    return True

def gcd(a, b):
    while b != 0:
        a, b = b, a % b
    return a

def mod_inverse(a, m):
    m0, x0, x1 = m, 0, 1
    while a > 1:
        q = a // m
        m, a = a % m, m
        x0, x1 = x1 - q * x0, x0
    return x1 + m0 if x1 < 0 else x1

def generate_keypair(p, q):
    n = p * q
    phi = (p - 1) * (q - 1)
    
    e = int(input("Enter public key exponent (e): "))
    
    while gcd(e, phi) != 1:
        e = int(input("Invalid choice. Please enter another public key exponent (e): "))
    
    d = mod_inverse(e, phi)
    
    return ((e, n), (d, n))

def encrypt(pk, plaintext):
    e, n = pk
    cipher = [pow(ord(char), e, n) for char in plaintext]
    return cipher

def decrypt(pk, ciphertext):
    d, n = pk
    plain = [chr(pow(char, d ,n)) for char in ciphertext]
    return ''.join(plain)


if __name__ == '__main__':
    
    p = int(input("Enter prime number p: "))
    
    while not is_prime(p):
        p = int(input("Invalid choice. Please enter another prime number p: "))
        
    q = int(input("Enter prime number q: "))
    
    while not is_prime(q) or q == p:
        q= int(input("Invalid choice. Please enter another prime number q: "))

    
    public_key,private_key=generate_keypair(p,q)
    
    message=input('Enter message to encrypt: ')
    
    encrypted_msg=encrypt(public_key,message)
    
    print('Encrypted Message:',encrypted_msg)
    
    decrypted_msg=decrypt(private_key ,encrypted_msg)
    
    print('Decrypted Message:',decrypted_msg)
