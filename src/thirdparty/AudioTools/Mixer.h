/*
 * (C) 2014-2022 see Authors.txt
 *
 * This file is part of MPC-HC.
 *
 * MPC-HC is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * MPC-HC is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#pragma once

#include "SampleFormat.h"
#include "../DSUtil/SimpleBuffer.h"

struct SwrContext;

class CMixer
{
private:
	SwrContext* m_pSWRCxt;
	double* m_matrix_dbl;
	double  m_center_level;
	double  m_surround_level;
	bool    m_normalize_matrix;
	bool    m_dummy_channels;
	bool    m_ActualContext;

	SampleFormat m_in_sf;
	SampleFormat m_out_sf;
	uint64_t m_in_layout;
	uint32_t m_out_layout;
	int     m_in_samplerate;
	int     m_out_samplerate;

	enum AVSampleFormat m_in_avsf;
	enum AVSampleFormat m_out_avsf;

	CSimpleBuffer<int32_t> m_Buffer1;
	CSimpleBuffer<int32_t> m_Buffer2;

public:
	CMixer();
	~CMixer();

private:
	bool Init();

public:
	void SetOptions(double center_level, double suround_level, bool normalize_matrix, bool dummy_channels);
	void UpdateInput (SampleFormat  in_sf, uint64_t in_layout, int  in_samplerate = 48000);
	void UpdateOutput(SampleFormat out_sf, uint32_t out_layout, int out_samplerate = 48000);

	int  Mixing(BYTE* pOutput, int out_samples, BYTE* pInput, int in_samples);

	int     Receive(BYTE* pOutput, int out_samples); // needed when using resampling
	int64_t GetDelay();                              // needed when using resampling
	int     CalcOutSamples(int in_samples);          // needed when using resampling
	void    FlushBuffers();                          // needed when using resampling
};
