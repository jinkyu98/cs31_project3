#include <iostream>
#include <string>
#include <cctype>
#include <cassert>

using namespace std;

bool isSyntacticallyCorrect(string pollData);
bool isValidStateCode(string stateCode);
bool isStateForecastZero(string pollData);
bool StateCodeTester(string pollData);
bool PartyCodeTester(string pollData);
bool DigitTester(string pollData);
bool UnauthroizedLetterTester(string pollData);
int tallyVotes(string pollData, char party, int& voteTally);	

int main()
{
	int votes = 999;
	
	assert((tallyVotes("", 'R', votes) == 0 && votes == 0));
	votes = 999;
	assert((tallyVotes("3CC", 'R', votes) == 1 && votes == 999));
	assert((tallyVotes("3Cae", 'R', votes) == 0 && votes == 0));
	assert((tallyVotes("3CAe99CAd19cae", 'e', votes) == 0 && votes == 22));
	votes = 999;
	assert((tallyVotes("3CAe99CAd19cae", 'E', votes) == 0 && votes == 22));
	votes = 999;
	assert((tallyVotes("3CA5", 'R', votes) == 1 && votes == 999));
	assert((tallyVotes("3Cae5MA", 'R', votes) == 1 && votes == 999));
	assert((tallyVotes("3Cae55MAK", 'R', votes) == 0 && votes == 0));
	votes = 999;
	assert((tallyVotes("3 Cae55MAK", 'R', votes) == 1 && votes == 999));
	assert((tallyVotes("3Cae55MAK", 'R', votes) == 0 && votes == 0));
	votes = 999;
	assert((tallyVotes("3Cae55MA@", 'R', votes) == 1 && votes == 999));
	assert((tallyVotes("Cae55MAK", '%', votes) == 1 && votes == 999));
	assert((tallyVotes("0Cae55MAK", 'K', votes) == 3 && votes == 999));
}


bool isValidStateCode(string stateCode)
{
	const string codes =
		"AL.AK.AZ.AR.CA.CO.CT.DE.DC.FL.GA.HI.ID.IL.IN.IA.KS."
		"KY.LA.ME.MD.MA.MI.MN.MO.MS.MT.NE.NV.NH.NJ.NM.NY.NC."
		"ND.OH.OK.OR.PA.RI.SC.SD.TN.TX.UT.VT.VA.WA.WV.WI.WY."
		"Al.Ak.Az.Ar.Ca.Co.Ct.De.Dc.Fl.Ga.Hi.Id.Il.In.Ia.Ks."
		"Ky.La.Me.Md.Ma.Mi.Mn.Mo.Ms.Mt.Ne.Nv.Nh.Nj.Nm.Ny.Nc."
		"Nd.Oh.Ok.Or.Pa.Ri.Sc.Sd.Tn.Tx.Ut.Vt.Va.Wa.Wv.Wi.Wy."
		"al.ak.az.ar.ca.co.ct.de.dc.fl.ga.hi.id.il.in.ia.ks."
		"ky.la.me.md.ma.mi.mn.mo.ms.mt.ne.nv.nh.nj.nm.ny.nc."
		"nd.oh.ok.or.pa.ri.sc.sd.tn.tx.ut.vt.va.wa.wv.wi.wy."
		"aL.aK.aZ.aR.cA.cO.cT.dE.dC.fL.gA.hI.iD.iL.iN.iA.kS."
		"kY.lA.mE.mD.mA.mI.mN.mO.mS.mT.nE.nV.nH.nJ.nM.nY.nC."
		"nD.oH.oK.oR.pA.rI.sC.sD.tN.tX.uT.vT.vA.wA.wV.wI.wY";
	return (stateCode.size() == 2 &&
		stateCode.find('.') == string::npos &&  // no '.' in stateCode
		codes.find(stateCode) != string::npos);  // match found
}
bool DigitTester(string pollData)
{
	int VoteTest = 0;

	// VoteTEst is used to check if digits are positioned correctly
	for (int k = 0; k < pollData.size(); k++)
	{
		// test if the last code ended with only a digit
		if (!isalpha(pollData.at(pollData.size() - 1)))
			VoteTest++;

		// test until the last state forecast
		else if (k + 5 <= pollData.size() - 1)
		{

			if (!isdigit(pollData.at(0)))
				VoteTest++;
			else if (isdigit(pollData.at(k)) && isdigit(pollData.at(k + 1)) && isdigit(pollData.at(k + 2)))
				VoteTest++;
			else if (isdigit(pollData.at(k)) && !isdigit(pollData.at(k + 1)) && !isdigit(pollData.at(k + 4)))
				VoteTest++;
			else if (isdigit(pollData.at(k)) && isdigit(pollData.at(k + 1)) && !isdigit(pollData.at(k + 5)))
				VoteTest++;
		}

		// test the last state forecast
		else
		{
			if (isalpha(pollData.at(pollData.size() - 3)) && !isdigit(pollData.at(pollData.size() - 4)))
				VoteTest++;
		}
	}

	// if digits are positioned correctly, it returns true
	if (VoteTest == 0)
		return true;
	else
		return false;
}
bool isStateForecastZero(string pollData)
{
	// if there is any state that cast zero, this function will return false
	int forecest = 0;
	for (int k = 0; k < pollData.size(); k++)
	{
		// checks digits in the first position
		if (k == 0 && pollData.at(k) == '0' && isalpha(pollData.at(k + 1)))
		{
			forecest = 1;
			break;
		}
		// tests digits in the middle position
		else if (k < pollData.size() - 5 && pollData.at(k) == '0' && isalpha(pollData.at(k - 1)) && isalpha(pollData.at(k + 1)))
		{
			forecest = 1;
			break;
		}
		// tests digits in the last position
		else if (k >= pollData.size() - 5 && pollData.at(pollData.size() - 4) == '0' && !isdigit(pollData.at(pollData.size() - 5)))
		{
			forecest = 1;
		}
		else
			forecest = 0;
	}
	// if 0 is found, this function will return false
	if (forecest == 0)
		return true;
	else
		return false;
}
bool StateCodeTester(string pollData)
{
	int Statecodetest = 0;
	// if statecode in the string is invalid, this function will return fals
	for (int k = 0; k < pollData.size(); k++)
	{
		// statecode must be resetted everytime to check multiple statecodes
		string Statecode = "";

		// if the vote is one-digit number
		if (k == 0 && isalpha(pollData.at(k + 1)))
		{
			Statecode += pollData.at(k + 1);
			Statecode += pollData.at(k + 2);
		}
		// if the vote is two-digit number
		else if (k == 0 && isdigit(pollData.at(k + 1)))
		{
			Statecode += pollData.at(k + 2);
			Statecode += pollData.at(k + 3);
		}
		// this tests the middle position in the string
		else if (k < pollData.size() - 5 && isdigit(pollData.at(k)) && isalpha(pollData.at(k + 1)))
		{
			Statecode += pollData.at(k + 1);
			Statecode += pollData.at(k + 2);
		}
		// this tests the last position of the string
		else if (k >= pollData.size() - 5)
		{
			Statecode += pollData.at(pollData.size() - 3);
			Statecode += pollData.at(pollData.size() - 2);
		}
		// in case k lands at a position other than state code. It only checks statecode.
		else
			Statecode = "CA";
		if (!isValidStateCode(Statecode))
			Statecodetest++;
	}
	// if statecode is invalid, this function will return false.
	if (Statecodetest == 0)
		return true;
	else
		return false;
}
bool PartyCodeTester(string pollData)
{
	int tester = 0;
	char Partycode;
	// this function tests if the partycode is in the right position and if it is a letter
	for (int k = 0; k < pollData.size(); k++)
	{
		//partycode is initialized to a character 'c' to make sure that tester is not increased when k lands a position where k is not the partycode
		Partycode = 'c';
		// if the vote is one-digit number
		if (k == 0 && pollData.size() >= 4 && isalpha(pollData.at(k + 1)))
		{
			Partycode = pollData.at(k + 3);
		}
		// if the vote is two-digit number
		else if (k == 0 && pollData.size() >= 4 && isdigit(pollData.at(k + 1)))
		{
			Partycode = pollData.at(k + 4);
		}
		// this tests the middle parts of the string
		else if (k < pollData.size() - 5 && isdigit(pollData.at(k)) && isalpha(pollData.at(k + 1)))
		{
			Partycode = pollData.at(k + 3);
		}
		// this tests the last part of the string
		else if (k >= pollData.size() - 5)
		{
			Partycode = pollData.at(pollData.size() - 1);
		}
		if (!isalpha(Partycode))
			tester++;
	}
	// if the partycode is invalid or is not in a correct position, this function will return false.
	if (tester == 0)
		return true;
	else
		return false;
}
bool UnauthroizedLetterTester(string pollData)
{
	// this function tests if the string is only composed of a letter and a digit
	int lettertester = 0;
	for (int k = 0; k < pollData.size(); k++)
	{
		if (!isdigit(pollData.at(k)) && !isalpha(pollData.at(k)))
			lettertester++;
	}
	// if there is a space or other symbols, this function will return false.
	if (lettertester == 0)
		return true;
	else
		return false;
}
bool isSyntacticallyCorrect(string pollData)
{
	int i = 0;
	// This lets a string that has a size less than 4 invalid
	if (pollData == "")
		i = 0;
	else if (pollData.size() < 4)
		i = 1;

	// If all of the test returns true, then this function will return true.
	// It means that the string is in a correct format.
	return (
		i == 0 &&
		DigitTester(pollData) &&
		StateCodeTester(pollData) &&
		PartyCodeTester(pollData) &&
		UnauthroizedLetterTester(pollData));
}
int tallyVotes(string pollData, char party, int& voteTally)
{
	// this part converts partycode into either uppercase or lowercase character
	char LowerPartyCode = tolower(party), UpperPartyCode = toupper(party);


	// if the string is not in a correct format, this function will return 1.
	if (!isSyntacticallyCorrect(pollData))
	{
		return 1;
	}
	// if the partycode is not a letter, this function will return 2.
	else if (!isalpha(party))
	{
		return 2;
	}
	// if any state casts zero votes on a particular party, this function will return 3.
	else if (!isStateForecastZero(pollData))
	{
		return 3;
	}
	// if none of the above situations occurred, then the total number of vote for the party will be calculated 
	// and this function will return 0.
	else
	{
		int i;
		// Resets the votecount since everything is valid
		voteTally = 0;

		// since an empty string is still a valid string, it will return 0.
		if (pollData == "")
		{
			return 0;
		}

		// this part counts the number of votes for a particular party.
		else
		{
			for (int k = 0; k <= pollData.size() - 1; k++)
			{
				string results = "";
				if (LowerPartyCode == pollData.at(k) || UpperPartyCode == pollData.at(k))
				{
					i = k;
					if (i == 3)
					{
						results += pollData.at(0);

						// the votecount will be in a string and should be converted into an integer.
						voteTally += stoi(results);
					}
					else if (i == 4)
					{
						// if the votecount is a two-digit number
						results += pollData.at(0);
						results += pollData.at(1);

						// the votecount will be in a string and should be converted into an integer.
						voteTally += stoi(results);
					}
					else if (i > 5 && isalpha(pollData.at(i - 4)))
					{
						results += pollData.at(i - 3);

						// the votecount will be in a string and should be converted into an integer.
						voteTally += stoi(results);
					}
					else if (i > 5 && isdigit(pollData.at(i - 4)))
					{
						// if the votecount is a two-digit number
						results += pollData.at(i - 4);
						results += pollData.at(i - 3);

						// the votecount will be in a string and should be converted into an integer.
						voteTally += stoi(results);
					}
				}
			}
			return 0;
		}
	}
}