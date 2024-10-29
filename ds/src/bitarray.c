
#include <stdio.h> /*printf, size_t*/
#include <string.h> /*strncat*/
#include <assert.h> /*assert*/
#include "bitarray.h" /*bitarray_t*/
#include <stdint.h> /*uint*/

bitarray_t SetAll(bitarray_t data)
{	
	data = ALL_BITS_ON_64; /*Dov said we have to get data as argument so i used it*/
	return data;
}



bitarray_t ResetAll(bitarray_t data)
{
	data = (bitarray_t)0; /*Dov said we have to get data as argument so i used it*/
	return data;
}



bitarray_t SetBitOn(bitarray_t data, size_t index)
{	
	return  data | (bitarray_t)1 << index;
}



bitarray_t SetBitOff(bitarray_t data, size_t index)
{
	return data & (~(1 << index));
}


bitarray_t SetBit(bitarray_t data, size_t index, bitarray_t bool_value)
{
	data = data | (bool_value << index);
	
	return data;
}



bitarray_t GetVal(bitarray_t data, size_t index)
{
	(data & (1 << index)) ? (data = 1) : (data = 0); 
	
	return (bitarray_t)data;
	
}


bitarray_t FlipBit(bitarray_t data, size_t index)
{

	data ^= (1 << index);
	
	return data;
}


int FlipAll(bitarray_t data)
{
	data ^= ALL_BITS_ON_64;
	
	return data;
}


/*My implementation before using LUT, which of course now look unnecessary*/
bitarray_t Mirror(bitarray_t data)
{

	data = ((data & 0x5555555555555555) << 1) | ((data & 0xAAAAAAAAAAAAAAAA) >> 1);
    data = ((data & 0x3333333333333333) << 2) | ((data & 0xCCCCCCCCCCCCCCCC) >> 2);
    data = ((data & 0x0F0F0F0F0F0F0F0F) << 4) | ((data & 0xF0F0F0F0F0F0F0F0) >> 4); 
    data = ((data & 0x00FF00FF00FF00FF) << 8) | ((data & 0xFF00FF00FF00FF00) >> 8); 
    data = ((data & 0x0000FFFF0000FFFF) << 16) | ((data & 0xFFFF0000FFFF0000) >> 16); 
    data = ((data & 0x00000000FFFFFFFF) << 32) | ((data & 0xFFFFFFFF00000000) >> 32); 

	return data;
}


bitarray_t RotateRight(bitarray_t data, size_t rotate_value)
{
	data = (data >> rotate_value) | (data << (NUM_OF_BITS - rotate_value));
	
	return data;
}



bitarray_t RotateLeft(bitarray_t data, size_t rotate_value)
{
	data = (data << rotate_value) | (data >> (NUM_OF_BITS- rotate_value));
	
	return data;
}


/*My implementation before using LUT, which of course now look unnecessary*/
/*I can explain this solution (its not mine of course, its Haming Weight)*/
size_t CountOn(bitarray_t data)
{
	
	data = ((data & 0x5555555555555555) + ((data >>  1) & 0x5555555555555555)); 
    data = ((data & 0x3333333333333333) + ((data >>  2) & 0x3333333333333333));
    data = ((data & 0x0F0F0F0F0F0F0F0F) + ((data >>  4) & 0x0F0F0F0F0F0F0F0F)); 
    data = ((data & 0x00FF00FF00FF00FF) + ((data >>  8) & 0x00FF00FF00FF00FF));  
    data = ((data & 0x0000FFFF0000FFFF) + ((data >> 16) & 0x0000FFFF0000FFFF));
    data = ((data & 0x00000000FFFFFFFF) + ((data >> 32) & 0x00000000FFFFFFFF)); 
     
	return data;
}


size_t CountOff(bitarray_t data)
{
	return NUM_OF_BITS - CountOn(data);	
}



char *ToString(bitarray_t data, char *buffer)
{
	size_t i = 0;
	data = Mirror(data);

	assert(NULL != buffer);

	for (; i < NUM_OF_BITS; ++i)
	{
		buffer[i] = (char)('0' + (1 & (data >> i)));
	}
	 /*buffer recived must be of size 64 + 1 to hold all the bits (64) and a 
	 null terminatoe*/
	buffer[NUM_OF_BITS + 1] = '\0';
	
	return buffer;
}




bitarray_t MirrorLUT(bitarray_t data)
{     
	bitarray_t mirrored_LUT[256] = {0};
	bitarray_t mirrored_data = 0;
    size_t i =0,j=0; 
    uint8_t mirrored_value = 0;
     
  	/*build the LUT of mirrored bytes*/
    for ( i = 0; i < 256; i++) 
    {
		mirrored_value = 0;
        for ( j = 0; j < BYTE_SIZE; j++) 
        {
            if (i & (1 << j)) 
            {
                mirrored_value |= (1 << (7 - j)); 
            }
        }
        mirrored_LUT[i] = mirrored_value; 
    }
 	
 	/*buld the result using mirrored bytes (bytes also being )*/
 	mirrored_data =((size_t)mirrored_LUT[data & 0xFF] << 56) |
        ((size_t)mirrored_LUT[(data >> 8) & 0xFF] << 48) |
        ((size_t)mirrored_LUT[(data >> 16) & 0xFF] << 40) |
        ((size_t)mirrored_LUT[(data >> 24) & 0xFF] << 32) |
        ((size_t)mirrored_LUT[(data >> 32) & 0xFF] << 24) |
        ((size_t)mirrored_LUT[(data >> 40) & 0xFF] << 16) |
        ((size_t)mirrored_LUT[(data >> 48) & 0xFF] << 8) |
        (size_t)mirrored_LUT[(data >> 56) & 0xFF];

    return mirrored_data;

}












bitarray_t CountOnLUT(bitarray_t num)
{

    int i=0;
    bitarray_t bit_set_LUT[256] = {0}; 
    
    for(i = 0; i < 256; i++)
    { 
        bit_set_LUT[i] = (i & 1) + bit_set_LUT[i / 2]; 
        
    } 

 
    return (bit_set_LUT[num & 0xff] + 
            bit_set_LUT[(num >> 8) & 0xff] + 
            bit_set_LUT[(num >> 16) & 0xff] + 
            bit_set_LUT[(num >> 24)& 0xff]+bit_set_LUT[(num >> 32)& 0xff]+
            bit_set_LUT[(num >> 40)& 0xff]+bit_set_LUT[(num >> 48)& 0xff]+
            bit_set_LUT[(num >> 56)& 0xff]); 


}
































