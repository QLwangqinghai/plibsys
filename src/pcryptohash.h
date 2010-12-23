/* 
 * 21.12.2010
 * Copyright (C) 2010 Alexander Saprykin <xelfium@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301  USA.
 */

/**
 * @file pcryptohash.h
 * @brief Cryptographic hash functions
 * @author Alexander Saprykin
 *
 * Cryptographic hash module supports following hash functions:
 * MD5, SHA-1 and GOST (R 34.11-94). Use p_crypto_hash_new() to initialize
 * new hash context with one of any mentioned above types. Data for hashing
 * can be added in several chunks of data using p_crypto_hash_update() routine.
 * You can add more chunks as long as hash context is opened. It becomes
 * closed in two cases: p_crypto_hash_get_string() or p_crypto_hash_get_digest()
 * was called. After that you can only get hash in hexidemical string or in raw
 * representation. Hash function type couldn't be changed after context
 * initialization.
 */

#if !defined (__PLIB_H_INSIDE__) && !defined (PLIB_COMPILATION)
#  error "Header files shouldn't be included directly, consider using <plib.h> instead."
#endif

#ifndef __PCRYPTOHASH_H__
#define __PCRYPTOHASH_H__

#include <pmacros.h>
#include <ptypes.h>

P_BEGIN_DECLS

/** Opaque data structure for handling cryptographic hash context. */
typedef struct _PCryptoHash PCryptoHash;

/**
 * Cryptographic hash function types for #PCryptoHash.
 * @since 0.0.1
 */
typedef enum {
	P_CRYPTO_HASH_TYPE_MD5		= 0, /**< MD5 hash function. */
	P_CRYPTO_HASH_TYPE_SHA1		= 1, /**< SHA-1 hash function. */
	P_CRYPTO_HASH_TYPE_GOST		= 2  /**< GOST (R 34.11-94) hash function.*/
} PCryptoHashType;

/**
 * @brief Initializes new #PCryptoHash context.
 * @param type Hash function type to use, can't be changed later.
 * @return Newly initialized #PCryptoHash context in case of success,
 * NULL otherwise.
 * @since 0.0.1
 */
P_LIB_API PCryptoHash *		p_crypto_hash_new		(PCryptoHashType	type);

/**
 * @brief Adds new chunk of data for hashing.
 * @param hash #PCryptoHash context to add @a data to.
 * @param data Data to add for hashing.
 * @param len Data length.
 * @note After calling p_crypto_hash_get_string() or p_crypto_hash_get_digest()
 * hash couldn't be updated anymore as it becomes closed.
 * @since 0.0.1
 */
P_LIB_API void			p_crypto_hash_update		(PCryptoHash		*hash,
								 const puchar		*data,
								 pssize			len);

/**
 * @brief Resets hash state.
 * @param hash #PCryptoHash context to reset.
 * @since 0.0.1
 *
 * After reset hash context becomes opened for updating, but all previously
 * added data will be lost. Hash function type couldn't be changed during or
 * after resets.
 */
P_LIB_API void			p_crypto_hash_reset		(PCryptoHash		*hash);

/**
 * @brief Gets hash in hexidemical representation.
 * @param hash #PCryptoHash context to get string from.
 * @return NULL-terminated string with hexidemical representation of the hash state
 * in case of success, NULL otherwise. String should be freed with p_free() after using it.
 * @note Before returning string hash context will be closed for further updates.
 * @since 0.0.1
 */
P_LIB_API pchar *		p_crypto_hash_get_string	(PCryptoHash		*hash);

/**
 * @brief Gets hash in raw representation.
 * @param hash #PCryptoHash context to get digest from.
 * @param buf Buffer to store digest with hash raw representation.
 * @param len Size of @a buf when calling, count of written bytes after.
 * @note Before getting raw digest hash context will be closed for further updates.
 * @since 0.0.1
 */
P_LIB_API void			p_crypto_hash_get_digest	(PCryptoHash		*hash,
								 puchar			*buf,
								 psize			*len);

/**
 * @brief Gets hash digest length depending on its type.
 * @param hash #PCryptoHash context to get length for.
 * @return Length (in bytes) of the given hash depending on its type in
 * case of success, -1 otherwise.
 * @note This length doesn't not match string hash representation.
 * @since 0.0.1
 */
P_LIB_API pssize		p_crypto_hash_get_length	(PCryptoHash		*hash);

/**
 * @brief Gets hash function type.
 * @param hash #PCryptoHash context to get type for.
 * @return Hash function type used in given context.
 * @since 0.0.1
 */
P_LIB_API PCryptoHashType	p_crypto_hash_get_type		(PCryptoHash		*hash);

/**
 * @brief Frees previously initialized hash context.
 * @param hash #PCryptoHash context to free.
 * @since 0.0.1
 */
P_LIB_API void			p_crypto_hash_free		(PCryptoHash		*hash);

P_END_DECLS

#endif /* __PFILE_H__ */