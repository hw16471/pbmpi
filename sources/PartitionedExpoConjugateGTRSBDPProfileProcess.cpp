
/********************

PhyloBayes MPI. Copyright 2010-2013 Nicolas Lartillot, Nicolas Rodrigue, Daniel Stubbs, Jacques Richer.

PhyloBayes is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License
as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
PhyloBayes is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

See the GNU General Public License for more details. You should have received a copy of the GNU General Public License
along with PhyloBayes. If not, see <http://www.gnu.org/licenses/>.

**********************/


#include "PartitionedExpoConjugateGTRSBDPProfileProcess.h"

void PartitionedExpoConjugateGTRSBDPProfileProcess::ToStream(ostream& os)	{

	os << Ncomponent << '\n';
	os << kappa << '\n';
	for (int j=0; j<GetDim(); j++)
	{
		os << dirweight[j] << '\t';
	}
	os << '\n';
	for (int i=0; i<Ncomponent; i++)
	{
		for (int j=0; j<GetDim(); j++)
		{
			os << profile[i][j] << '\t';
		}
		os << '\n';
	}
	for (int i=0; i<GetNsite(); i++)
	{
		os << alloc[i] << '\t';
	}
	os << '\n';

	for(int p = 0; p < GetNpart(); p++)
	{
		if(!fixrr[p])
		{
			for (int i=0; i<GetNrr(); i++)	{
				os << rr[p][i] << '\t';
			}
			os << '\n';
		}
	}
}

void PartitionedExpoConjugateGTRSBDPProfileProcess::FromStream(istream& is)	{

	is >> Ncomponent;
	is >> kappa;
	
	for (int i=0; i<GetDim(); i++)
	{
		is >> dirweight[i];
	}

	for (int i=0; i<Ncomponent; i++)
	{
		for (int j=0; j<GetDim(); j++)
		{
			is >> profile[i][j];
		}
	}

	for (int i=0; i<GetNsite(); i++)
	{
		is >> alloc[i];
	}

	for(int p = 0; p < GetNpart(); p++)
	{
		if(!fixrr[p])
		{
			for (int i=0; i<GetNrr(); i++)
				is >> rr[p][i];
		}
	}

	ResampleWeights();
	// CHECK some update here ?
}