
#ifndef IMGLOADER_HPP_
# define IMGLOADER_HPP_

# include <exception>
# include <iostream>

# pragma pack(2)

typedef struct
{
  unsigned short	magic;
  unsigned int		bmp_size;
  unsigned int		id_app;
  unsigned int		start_offset;
}		t_bmp_header;

typedef struct
{
  unsigned int		img_header_size;
  unsigned int		width;
  unsigned int		height;
  unsigned short	nb_plan;
  unsigned short	bpp;
  unsigned int		compression;
  unsigned int		img_size;
  unsigned int		wppm;
  unsigned int		hppm;
  unsigned int		palette;
  unsigned int		important_color;
}		t_bmp_img_header;

#pragma pack()

class BmpLoader
{
private:

  unsigned char		*_data;
  unsigned int		_allocated_size;
  unsigned int		_width;
  unsigned int		_height;

public:

  BmpLoader();
  ~BmpLoader();


  unsigned char		*getBmpData(const std::string &path);
  void			deleteData(void);
  unsigned int		getSize(void) const {return _allocated_size;}
  unsigned int		getWidth(void) const {return _width;}
  unsigned int		getHeight(void) const {return _width;}
};

#endif
