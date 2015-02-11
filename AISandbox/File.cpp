#include "File.h"
#include <sstream>
#include <assert.h>
bool File::OpenRead(const std::string& filename, bool isBinary)
{
	assert(!m_file.is_open());
	std::ios_base::openmode mode = std::ios::in;
	if(isBinary){mode |= std::ios::binary;}
	m_file.open(filename.c_str(),mode);
	std::string str;
	std::getline(m_file,str);
	if(str.size()==1)
	{
		comment_=str[0];
	}
	else
	{
		comment_='#';
	}

	line_=0;
	filename_=filename;
	m_file.seekg(0,std::ios::beg);
	return (m_file.is_open());
}

void File::Close()
{


	m_file.close();
	comment_=NULL;
	filename_="";
	line_=0;
}

int File::GetLineNum()const
{	
	return line_;
}



bool File::OpenWrite(const std::string& filename)
{
	assert(!m_file.is_open());
	m_file.open(filename.c_str());
	line_=0;
	return(m_file.is_open());
}

int File::GetBinary(unsigned int bytes, unsigned char* pBuffer)
{
	assert(m_file.is_open());
	if(m_file.eof())
	{
		return 0;
	}
	m_file.read((char*)pBuffer,bytes);
	return bytes;
}
void File::BinarySeek(unsigned int seekPos)
{
	m_file.seekg(seekPos);
}
bool File::GetString(std::string* result)
{
	assert(m_file.is_open());
	if (m_file.eof())
	{
		return false;
	}
	std::string temp;
	while(!m_file.eof())
	{
		++line_;
		std::getline(m_file,temp);
		if(temp.size()==0)
		{
			continue;
		}
		else if(temp.front()==comment_||temp.front()==' ')
		{
			continue;
		}
		else
		{
			*result=temp;

			return true;
		}
	}
	return false;
}

bool File::GetCSVec2i(Vec2i * result)
{
	std::string temp;
	Vec2i vec;
	if(!GetString(&temp))
	{
		return false;
	}
	int j=0;
	for(int i=0;i<(int)temp.size();++i)
	{
		if(temp[i]==',')
		{
			j=i;
		}
	}
	vec.x=atoi(temp.substr(0,j+1).c_str());
	vec.y=atoi(temp.substr(j+1,temp.size()-j).c_str());
	*result=vec;
	return true;
}

bool File::GetCSVec3i(Vec3i* result)
{
	std::string temp;
	Vec3i vec;
	if(!GetString(&temp))
	{
		return false;
	}
	int firstC=0;
	int secondC=0;
	for(int i=0;i<(int)temp.size();++i)
	{
		if(temp[i]==',')
		{
			if(firstC)
			{
				secondC=i;
			}
			else
			{
				firstC=i;
			}
		}
	}
	vec.x=atoi(temp.substr(0,firstC+1).c_str());
	vec.y=atoi(temp.substr(firstC+1,secondC-firstC).c_str());
	vec.z=atoi(temp.substr(secondC+1,temp.size()-secondC+firstC).c_str());
	*result=vec;
	return true;
}

bool File::GetCSVec2f(Vec2f * result)
{
	std::string temp;
	Vec2f vec;
	if(!GetString(&temp))
	{
		return false;
	}
	int j=0;
	for(int i=0;i<(int)temp.size();++i)
	{
		if(temp[i]==',')
		{
			j=i;
		}
	}
	vec.x=(float)atof(temp.substr(0,j+1).c_str());
	vec.y=(float)atof(temp.substr(j+1,temp.size()-j).c_str());
	*result=vec;
	return true;
}

bool File::GetCSVec3f(Vec3f* result)
{
	std::string temp;
	Vec3f vec;
	if(!GetString(&temp))
	{
		return false;
	}
	int firstC=0;
	int secondC=0;
	for(int i=0;i<(int)temp.size();++i)
	{
		if(temp[i]==',')
		{
			if(firstC)
			{
				secondC=i;
			}
			else
			{
				firstC=i;
			}
		}
	}
	vec.x=(float)atof(temp.substr(0,firstC+1).c_str());
	vec.y=(float)atof(temp.substr(firstC+1,secondC-firstC).c_str());
	vec.z=(float)atof(temp.substr(secondC+1,temp.size()-secondC+firstC).c_str());
	*result=vec;
	return true;
}

bool File::GetBool(bool* result)
{
	std::string temp;
	if(!GetString(&temp))
	{
		return false;
	}
	int boolie;
	boolie=atoi(temp.c_str());
	if(boolie!=0)
	{
		*result=true;
		return true;
	}
	*result=false;
	return true;
}

bool File::GetFloat(float * result)
{
	std::string temp;
	if(!GetString(&temp))
	{
		return false;
	}
	*result=(float)atof(temp.c_str());
	return true;
}

bool File::GetInteger(int* result)
{
	std::string temp;
	if(!GetString(&temp))
	{
		return false;
	}
	*result=atoi(temp.c_str());
	return true;
}

bool File::WriteString(std::string writey)
{
	assert(m_file.is_open());
	if(line_==0)
	{
		m_file<<'#'<<std::endl;
		++line_;
	}
	m_file<<writey;
	return true;
}

bool File::WriteInt(int inty)
{
	assert(m_file.is_open());
	if(line_==0)
	{
		m_file<<'#'<<std::endl;
		++line_;
	}
	m_file<<inty;
	++line_;
	return true;
}

bool File::WriteFloat(float floaty)
{
	assert(m_file.is_open());
	if(line_==0)
	{
		m_file<<'#'<<std::endl;
		++line_;
	}
	m_file<<floaty;
	++line_;
	return true;
}

File::File()
{

}

File::~File()
{

	m_file.close();
}

std::string File::GetFileName()
{
	return filename_;
}