
#ifndef _CCCRYPTO_H_
#define _CCCRYPTO_H_


class CCCrypto
{
public:
	static const int MD5_BUFFER_LENGTH = 16;
	static const int SHA1_BUFFER_LENGTH = 20;
    
    /** @brief Encoding data with Base64 algorithm, return encoded string length */
    static int encodeBase64(const void* input, int inputLength,
                            char* output, int outputBufferLength);
    
    
    /** @brief Decoding Base64 string to data, return decoded data length */
    static int decodeBase64(const char* input,
                            void* output, int outputBufferLength);
    
    /** @brief Calculate MD5, get MD5 code (not string) */
    static void MD5(void* input, int inputLength,
                    unsigned char* output);
    
    /** @brief Calculate SHA1 with a secret key. */
    static void sha1(unsigned char* input, int inputLength,
                     unsigned char* key, int keyLength,
                     unsigned char* buffer, int bufferLength); 
private:
    CCCrypto(void) {}
};

#endif // __CC_EXTENSION_CCCRYPTO_H_
