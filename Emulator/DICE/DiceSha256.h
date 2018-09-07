/*
 * Copyright (c) 2000-2001, Aaron D. Gifford
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the copyright holder nor the names of contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTOR(S) ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTOR(S) BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

//
// 4-MAY-2015; Adaptation (DennisMa;MSFT).
//
#ifndef __DICE_CRYPTO_SHA256_H__
#define __DICE_CRYPTO_SHA256_H__

#ifdef __cplusplus
extern "C" {
#endif

#pragma CHECKED_SCOPE ON

typedef uint8_t  dice_sha2_uint8_t;  // Exactly 1 byte
typedef uint32_t dice_sha2_word32;   // Exactly 4 bytes
typedef uint64_t dice_sha2_word64;   // Exactly 8 bytes

#define SHA256_BLOCK_LENGTH         64
#define SHA256_DIGEST_LENGTH        32

typedef uint64_t dice_hashMagic_t;

#if HOST_IS_LITTLE_ENDIAN
#define HASH_MAGIC_VALUE    (0x4078746368736168LL)
#else
#define HASH_MAGIC_VALUE    (0x6861736863747840LL)
#endif

typedef struct _DICE_SHA256_CONTEXT {
    uint32_t    state[8] : itype(uint32_t _Checked[8]);
    dice_hashMagic_t magic;
    uint64_t    bitcount;
    uint8_t     buffer[SHA256_BLOCK_LENGTH] : itype(uint8_t _Checked[SHA256_BLOCK_LENGTH]);
} DICE_SHA256_CONTEXT;

//
// Initialize the hash context
// @param context the hash context
//
void DICE_SHA256_Init(DICE_SHA256_CONTEXT *context : itype(_Ptr<DICE_SHA256_CONTEXT>));

//
// Update the digest using the specific bytes
// @param context the hash context
// @param buf the bytes to digest
// @param bufSize the number of bytes to digest
//
void DICE_SHA256_Update(DICE_SHA256_CONTEXT *context : itype(_Ptr<DICE_SHA256_CONTEXT>),
                        const dice_sha2_uint8_t *data : itype(_Array_ptr<const dice_sha2_uint8_t>) byte_count(len), 
                        size_t len);

//
// Retrieve the final digest
// @param context the hash context
// @param digest the buffer to hold the digest.  Must be of size SHA256_DIGEST_LENGTH
//
void DICE_SHA256_Final(DICE_SHA256_CONTEXT *context : itype(_Ptr<DICE_SHA256_CONTEXT>), 
                       dice_sha2_uint8_t *digest : itype(_Array_ptr<dice_sha2_uint8_t>) byte_count(SHA256_DIGEST_LENGTH));

//
// Hash a block of data
// @param context the hash context
// @param buf the buffer containing the data to hash
// @param bufSize the number of bytes in the buffer
// @param digest the buffer to hold the digest.  Must be of size SHA256_DIGEST_LENGTH
//
void DiceSHA256Ctx(DICE_SHA256_CONTEXT *context : itype(_Ptr<DICE_SHA256_CONTEXT>),
                   const uint8_t *buf : itype(_Array_ptr<const uint8_t>) byte_count(bufSize), 
                   size_t bufSize,
                   uint8_t *digest : itype(_Array_ptr<uint8_t>) byte_count(SHA256_DIGEST_LENGTH));

//
// Hash a block of data
// @param buf the buffer containing the data to hash
// @param bufSize the number of bytes in the buffer
// @param digest the buffer to hold the digest.  Must be of size SHA256_DIGEST_LENGTH
//
void DiceSHA256(const uint8_t *buf : itype(_Array_ptr<const uint8_t>) byte_count(bufSize), 
                size_t bufSize,
                uint8_t *digest : itype(_Array_ptr<uint8_t>) byte_count(SHA256_DIGEST_LENGTH));

void DiceSHA256_2(const uint8_t *buf1 : itype(_Array_ptr<const uint8_t>) byte_count(bufSize1), size_t bufSize1, 
                  const uint8_t *buf2 : itype(_Array_ptr<const uint8_t>) byte_count(bufSize2), size_t bufSize2,
                  uint8_t *digest : itype(_Array_ptr<uint8_t>) byte_count(SHA256_DIGEST_LENGTH));

#pragma CHECKED_SCOPE OFF

#ifdef __cplusplus
}
#endif

#endif