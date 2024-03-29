
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
#include "BmpLoader.hpp"

BmpLoader::BmpLoader() :
  _data(NULL),
  _allocated_size(0)
{
}

BmpLoader::~BmpLoader()
{
  if (_data)
    delete[] _data;
}

unsigned char		*BmpLoader::getBmpData(const std::string &path)
{
  int			fd;
  t_bmp_header	header;
  t_bmp_img_header	img_header;

  std::cout << "path : " << path << std::endl;
  if ((fd = open(path.c_str(), O_RDONLY)) == -1)
    {
      std::cerr << "Cannot open file " << path << std::endl;
      close(fd);
      return NULL;
    }
  if ((read(fd, &header, sizeof(header))) < 1)
    {
      std::cerr << "Cannot read file " << path << std::endl;
      close(fd);
      return NULL;
    }
  if ((read(fd, &img_header, sizeof(img_header))) < 1)
    {
      std::cerr << "Cannot read file " << path << std::endl;
      close(fd);
      return NULL;
    }

  unsigned int size = img_header.width * img_header.height * (img_header.bpp / 8);
  try
    {
      if (_allocated_size != size)
	{
	  delete[] _data;
	  _data = NULL;
	}
      if (!_data)
	{
	  std::cout << "allocation de " << size << std::endl;
	  _data = new unsigned char[size];
	}
    }
  catch (std::exception& e)
    {
      std::cerr << "Error : " <<  e.what() << std::endl;
      close(fd);
      return NULL;
    }
  _allocated_size = size;
  if ((read(fd, _data, size)) < 1)
    {
      std::cerr << "Cannot read file data " << path << std::endl;
      close(fd);
      return NULL;
    }
  close(fd);
  _width = img_header.width;
  _height = img_header.height;
  return _data;
}

void		BmpLoader::deleteData(void)
  {
    if (_data)
      delete[] _data;
    _data = NULL;
  }
