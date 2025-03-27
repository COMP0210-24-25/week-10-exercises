unsigned long rubbish_hash(unsigned int x)
{
    unsigned long x_temp = x;
    for(int i = 0; i < 7; i++)
    {
        x_temp = (x_temp * x) % 919393;
    }
    return x_temp;
}