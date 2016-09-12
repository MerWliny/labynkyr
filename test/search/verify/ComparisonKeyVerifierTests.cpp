/*
 * University of Bristol – Open Access Software Licence
 * Copyright (c) 2016, The University of Bristol, a chartered
 * corporation having Royal Charter number RC000648 and a charity
 * (number X1121) and its place of administration being at Senate
 * House, Tyndall Avenue, Bristol, BS8 1TH, United Kingdom.
 * All rights reserved
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above
 * copyright notice, this list of conditions and the following
 * disclaimer in the documentation and/or other materials provided
 * with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *
 * Any use of the software for scientific publications or commercial
 * purposes should be reported to the University of Bristol
 * (OSI-notifications@bristol.ac.uk and quote reference 2514). This is
 * for impact and usage monitoring purposes only.
 *
 * Enquiries about further applications and development opportunities
 * are welcome. Please contact elisabeth.oswald@bristol.ac.uk
*/
/*
 * ComparisonKeyVerifierTests.cpp
 *
 */

#include "src/labynkyr/search/verify/ComparisonKeyVerifier.hpp"

#include <unittest++/UnitTest++.h>

#include <stdint.h>

#include <vector>

namespace labynkyr {
namespace search {

TEST(ComparisonKeyVerifier_keysChecked) {
	std::vector<uint8_t> const expected = {0x01, 0x02, 0x03};
	ComparisonKeyVerifier<24> verifier(expected);
	CHECK_EQUAL(0, verifier.keysChecked());
	verifier.checkKey(std::vector<uint8_t>{0x02, 0x02, 0x03});
	CHECK_EQUAL(1, verifier.keysChecked());
	verifier.checkKey(std::vector<uint8_t>{0x02, 0x02, 0x03});
	CHECK_EQUAL(2, verifier.keysChecked());
	verifier.checkKey(std::vector<uint8_t>{0x02, 0x02, 0x03});
	CHECK_EQUAL(3, verifier.keysChecked());
}

TEST(ComparisonKeyVerifier_success) {
	std::vector<uint8_t> const expected = {0x01, 0x02, 0x03};
	ComparisonKeyVerifier<24> verifier(expected);
	CHECK_EQUAL(false, verifier.success());
	verifier.checkKey(std::vector<uint8_t>{0x02, 0x02, 0x03});
	CHECK_EQUAL(false, verifier.success());
	verifier.checkKey(std::vector<uint8_t>{0x01, 0x02, 0x03});
	CHECK_EQUAL(true, verifier.success());
	verifier.checkKey(std::vector<uint8_t>{0x02, 0x02, 0x03});
	CHECK_EQUAL(true, verifier.success());
}

TEST(ComparisonKeyVerifier_correctKey_success) {
	std::vector<uint8_t> const expected = {0x01, 0x02, 0x03};
	ComparisonKeyVerifier<24> verifier(expected);
	verifier.checkKey(std::vector<uint8_t>{0x02, 0x02, 0x03});
	verifier.checkKey(std::vector<uint8_t>{0x01, 0x02, 0x03});
	verifier.checkKey(std::vector<uint8_t>{0x02, 0x02, 0x03});
	auto correctKey = verifier.correctKey();
	CHECK_ARRAY_EQUAL(expected, correctKey.asBytes(), expected.size());
}

TEST(ComparisonKeyVerifier_correctKey_fail) {
	std::vector<uint8_t> const expected = {0x01, 0x02, 0x03};
	ComparisonKeyVerifier<24> verifier(expected);
	verifier.checkKey(std::vector<uint8_t>{0x02, 0x02, 0x03});
	verifier.checkKey(std::vector<uint8_t>{0x02, 0x02, 0x03});
	verifier.checkKey(std::vector<uint8_t>{0x02, 0x02, 0x03});
	CHECK_THROW(verifier.correctKey(), std::logic_error);
}

} /* namespace search */
} /* namespace labynkyr */
