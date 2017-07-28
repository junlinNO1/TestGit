#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <map>


std::string & Trim(std::string & str)
{
	int nonEmptyBeginIndex = 0, nonEmptyEndIndex = str.length();
	while (nonEmptyBeginIndex < nonEmptyEndIndex)
	{
		if (str[nonEmptyBeginIndex] == ' ' || str[nonEmptyBeginIndex] == '\t')
			++ nonEmptyBeginIndex;
		if (str[nonEmptyEndIndex - 1] == ' ' || str[nonEmptyEndIndex - 1] == '\t')
			--nonEmptyEndIndex;

		if (str[nonEmptyBeginIndex] != ' ' && str[nonEmptyBeginIndex] != '\t'
			&& str[nonEmptyEndIndex - 1] != ' ' && str[nonEmptyEndIndex - 1] != '\t')
			break;
	}

	str = str.substr(nonEmptyBeginIndex, nonEmptyEndIndex - nonEmptyBeginIndex);
	return str;
}

void Split(std::string str, std::string strDelimiter, std::vector<std::string> & vecSplits)
{
	vecSplits.clear();
	size_t start = 0;
	size_t found = str.find(strDelimiter, start);
	while (found != std::string::npos)
	{
		std::string strSplit = Trim(str.substr(start, found - start));
		vecSplits.push_back(strSplit);
		start = found + 1;
		found = str.find(strDelimiter, start);
	}
	std::string strSplit = Trim(str.substr(start, found - start));
	vecSplits.push_back(strSplit);
}

typedef struct stSong 
{
	int m_id;
	std::string m_genre;
	std::string m_artist;
	std::string m_album;
	std::string m_song;

	stSong(int id, std::string strGenre, std::string strArtist, std::string strAlbum, std::string strSong)
		:m_id(id), m_genre(strGenre), m_artist(strArtist), m_album(strAlbum), m_song(strSong)
	{
	}

} SONG_S;


char * SongFilter(char * collection[], int cNum, char * filterinfos[], int fNum)
{
	if (NULL == collection || 0 == cNum || NULL == filterinfos || 0 == fNum)
		return "";

	std::vector<std::string> vecSplits;
	std::map<std::string, std::vector<std::string> > mapFilters;
	for (int i = 0; i < fNum; ++i)
	{
		Split(filterinfos[i], "=", vecSplits);
		if (2 != vecSplits.size()) continue;
		mapFilters[vecSplits[0]].push_back(vecSplits[1]);
	}

	std::vector<SONG_S> vecSongs;
	for (int j = 0; j < cNum; ++j)
	{
		Split(collection[j], "-", vecSplits);
		if (4 != vecSplits.size()) continue;
		vecSongs.push_back(SONG_S(j, vecSplits[0], vecSplits[1], vecSplits[2], vecSplits[3]));
	}

	int totalStrLen = 0;
	std::vector<int> vecResult;
	std::vector<SONG_S>::iterator itrSong = vecSongs.begin();
	for (; vecSongs.end() != itrSong; ++itrSong)
	{
		std::map<std::string, std::vector<std::string> >::iterator itrFilter = mapFilters.begin();
		for (; mapFilters.end() != itrFilter; ++itrFilter)
		{
			if (itrFilter->first == "genre" && itrFilter->second.end() == 
				std::find(itrFilter->second.begin(), itrFilter->second.end(), itrSong->m_genre))
					break;
			if (itrFilter->first == "artist" && itrFilter->second.end() == 
				std::find(itrFilter->second.begin(), itrFilter->second.end(), itrSong->m_artist))
					break;
			if (itrFilter->first == "album" && itrFilter->second.end() == 
				std::find(itrFilter->second.begin(), itrFilter->second.end(), itrSong->m_album))
					break;
			if (itrFilter->first == "song" && itrFilter->second.end() == 
				std::find(itrFilter->second.begin(), itrFilter->second.end(), itrSong->m_song))
					break;
		}

		if (mapFilters.end() != itrFilter) continue;
		vecResult.push_back(itrSong->m_id);
		totalStrLen += strlen(collection[itrSong->m_id]);
	}

	if (vecResult.size() == 0) return "";
	totalStrLen += vecResult.size();
	char * pRet = (char*)malloc(totalStrLen * sizeof(char));
	if (NULL == pRet) return "";
	for (int i = 0, offset = 0; i < vecResult.size(); ++i)
	{
		strcpy(pRet + offset, collection[vecResult[i]]);
		offset += strlen(collection[vecResult[i]]);
		pRet[offset++] = ',';
	}
	pRet[totalStrLen - 1] = '\0';
	return pRet;
}


int main()
{
	//genre-artist-album-song
	char * collection[] = { "add-lenign ds-jj-ainini", "fork-lenign ds-hj-ainini", "fork-ainini-   hj -loving you", "fork-sadfadf-fd-loving you" };
	char * filterinfo[] = { "genre=fork", "album=hj" };

	char *pResult = SongFilter(collection, sizeof(collection) / sizeof(char*), filterinfo, sizeof(filterinfo) / sizeof(char*));

	return 0;
}