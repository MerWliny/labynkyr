%%
% University of Bristol – Open Access Software Licence
% Copyright (c) 2016, The University of Bristol, a chartered
% corporation having Royal Charter number RC000648 and a charity
% (number X1121) and its place of administration being at Senate
% House, Tyndall Avenue, Bristol, BS8 1TH, United Kingdom.
% All rights reserved
%
% Redistribution and use in source and binary forms, with or without
% modification, are permitted provided that the following conditions
% are met:
%
% 1. Redistributions of source code must retain the above copyright
% notice, this list of conditions and the following disclaimer.
%
% 2. Redistributions in binary form must reproduce the above
% copyright notice, this list of conditions and the following
% disclaimer in the documentation and/or other materials provided
% with the distribution.
%
% THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
% "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
% LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
% FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
% COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
% INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
% (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
% SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
% HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
% STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
% ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
% OF THE POSSIBILITY OF SUCH DAMAGE.
%
% Any use of the software for scientific publications or commercial
% purposes should be reported to the University of Bristol
% (OSI-notifications@bristol.ac.uk and quote reference 2514). This is
% for impact and usage monitoring purposes only.
%
% Enquiries about further applications and development opportunities
% are welcome. Please contact elisabeth.oswald@bristol.ac.uk
%%

%% Add JAR to classpath
javaclasspath 'LabynkyrRankJ-1.0-jar-with-dependencies.jar'

%% Parameters
key = '000102030405060708090A0B0C0D0E0F';
precisionBits = int32(15);
vectorCount = int32(16);
vectorSizeBits = int32(8);

%% Example 1
%
% 35 traces, ~rank 2^45
%
% Prepare scores
get_scores_1;
scores = reshape(scores', 1, 256 * 16);
scores = log2(scores);
scores = abs(scores);

% Rank
disp('Running example 1:');
logRank = uk.ac.bristol.labynkyr.Rank.logRankKey(key, precisionBits, vectorCount, vectorSizeBits, scores);
fprintf(1, '  log2(rank) = %.5f\n', logRank);

%% Example 2
%
% 15 traces, rank ~2^106
%
% Prepare scores
get_scores_2;
scores = reshape(scores', 1, 256 * 16);
scores = log2(scores);
scores = abs(scores);

% Rank
disp('Running example 2:');
logRank = uk.ac.bristol.labynkyr.Rank.logRankKey(key, precisionBits, vectorCount, vectorSizeBits, scores);
fprintf(1, '  log2(rank) = %.5f\n', logRank);

%% Example 3
%
% 90 traces,, rank ~2^5
%
% Prepare scores
get_scores_3;
scores = reshape(scores', 1, 256 * 16);
scores = log2(scores);
scores = abs(scores);

% Rank
disp('Running example 3:');
logRank = uk.ac.bristol.labynkyr.Rank.logRankKey(key, precisionBits, vectorCount, vectorSizeBits, scores);
fprintf(1, '  log2(rank) = %.5f\n', logRank);
