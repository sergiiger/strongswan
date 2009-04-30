/*
 * Copyright (C) 2005-2006 Martin Willi
 * Copyright (C) 2005 Jan Hutter
 * Hochschule fuer Technik Rapperswil
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.  See <http://www.fsf.org/copyleft/gpl.txt>.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 */
 
/**
 * @defgroup prf prf
 * @{ @ingroup crypto
 */

#ifndef PRF_H_
#define PRF_H_

typedef enum pseudo_random_function_t pseudo_random_function_t;
typedef struct prf_t prf_t;

#include <library.h>

/**
 * Pseudo random function, as in IKEv2 RFC 3.3.2.
 *
 * PRF algorithms not defined in IKEv2 are allocated in "private use"
 * space.
 */
enum pseudo_random_function_t {
	PRF_UNDEFINED = 1024,
	/** Implemented via hmac_prf_t. */
	PRF_HMAC_MD5 = 1,
	/** Implemented via hmac_prf_t. */
	PRF_HMAC_SHA1 = 2,
	PRF_HMAC_TIGER = 3,
	PRF_AES128_XCBC = 4,
	/** Implemented via hmac_prf_t. */
	PRF_HMAC_SHA2_256 = 5,
	/** Implemented via hmac_prf_t. */
	PRF_HMAC_SHA2_384 = 6,
	/** Implemented via hmac_prf_t. */
	PRF_HMAC_SHA2_512 = 7,
	/** Implemented via fips_prf_t, other output sizes would be possible */
	PRF_FIPS_SHA1_160 = 1025,
	/** Could be implemented via fips_prf_t, uses fixed output size of 160bit */
	PRF_FIPS_DES = 1026,
	/** 
	 * Keyed hash algorithm using SHA1, used in EAP-AKA:
	 * This PRF uses SHA1, but XORs the key into the IV. No "Final()" operation
	 * is applied to the SHA1 state. */
	PRF_KEYED_SHA1 = 1027,
};

/**
 * enum name for encryption_algorithm_t.
 */
extern enum_name_t *pseudo_random_function_names;

/**
 * Generic interface for pseudo-random-functions.
 */
struct prf_t {
	/**
	 * Generates pseudo random bytes and writes them in the buffer.
	 *
	 * @param seed		a chunk containing the seed for the next bytes
	 * @param buffer	pointer where the generated bytes will be written
	 */
	void (*get_bytes) (prf_t *this, chunk_t seed, u_int8_t *buffer);
	
	/**
	 * Generates pseudo random bytes and allocate space for them.
	 * 
	 * @param seed		a chunk containing the seed for the next bytes
	 * @param chunk		chunk which will hold generated bytes
	 */
	void (*allocate_bytes) (prf_t *this, chunk_t seed, chunk_t *chunk);
	
	/**
	 * Get the block size of this prf_t object.
	 * 
	 * @return			block size in bytes
	 */
	size_t (*get_block_size) (prf_t *this);
	
	/**
	 * Get the key size of this prf_t object.
	 *
	 * This is a suggestion only, all implemented PRFs accept variable key
	 * length.
	 * 
	 * @return			key size in bytes
	 */
	size_t (*get_key_size) (prf_t *this);
	
	/**
	 * Set the key for this prf_t object.
	 * 
	 * @param key		key to set
	 */
	void (*set_key) (prf_t *this, chunk_t key);
	
	/**
	 * Destroys a prf object.
	 */
	void (*destroy) (prf_t *this);
};

#endif /** PRF_H_ @}*/
