#include <stdlib.h>
#include <string.h>

#include "CCCrypto.h"

extern "C" {
#include "base64/libb64.h"
#include "md5/md5.h"
#include "sha1/sha1.h"
}

int CCCrypto::encodeBase64(const void* input,
                           int inputLength,
                           char* output,
                           int outputBufferLength)
{
    int bufferSize = 2 * inputLength;
    char* buffer = (char*)malloc(bufferSize);
    memset(buffer, 0, bufferSize);
    
    base64_encodestate state;
    base64_init_encodestate(&state);
    int r1 = base64_encode_block(static_cast<const char*>(input), inputLength, buffer, &state);
    int r2 = base64_encode_blockend(buffer+ r1, &state);
    
    int dataUsed = r1 + r2;
    
    memset(output, 0, outputBufferLength);
    int cp = dataUsed < outputBufferLength ? dataUsed : outputBufferLength - 1;
    memcpy(output, buffer, cp);
    free(buffer);
    return cp;
}

int CCCrypto::decodeBase64(const char* input,
                           void* output,
                           int outputBufferLength)
{
    int bufferSize = strlen(input) + 1;
    char* buffer = (char*)malloc(bufferSize);
    memset(buffer, 0, bufferSize);
    base64_decodestate state;
    base64_init_decodestate(&state);
    int r1 = base64_decode_block(input, bufferSize - 1, buffer, &state);
    
    memset(output, 0, outputBufferLength);
    int cp = r1 < outputBufferLength ? r1 : outputBufferLength - 1;
    memcpy(output, buffer, cp);
    free(buffer);
    return cp;
}

void CCCrypto::MD5(void* input, int inputLength, unsigned char* output)
{
    MD5_CTX ctx;
    MD5_Init(&ctx);
    MD5_Update(&ctx, input, inputLength);
    MD5_Final(output, &ctx);
}

void CCCrypto::sha1(unsigned char* input, int inputLength,
                    unsigned char* key, int keyLength,
                    unsigned char* buffer, int bufferLength)
{
	SHA1 sha1;
	sha1.addBytes(input, inputLength);
	sha1.addBytes(key, keyLength);
	sha1.getDigest(buffer, bufferLength);
}

