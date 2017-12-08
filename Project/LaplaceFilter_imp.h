//
// Created by shernand on 12/8/17.
//

template<typename T> LaplaceFilter<T>::LaplaceFilter() : StandardFilter<T>()
{
    this->setLength(5);
    int pLength = this->length;
    std::vector<T> pMask =this->mask;
    pMask = std::vector<T>(pLength);
    //\todo Find a way to implement the Laplace with iota or foreach
    //Fills the mask
    int half = pLength/2;
    for(int i = 0; i<=half;i++){
        pMask[i] = 1;
        pMask[pLength-1-i] = 1;
    }
    pMask[half]=-(pLength-1);
    this->setMask(pMask);
}
template<typename T> LaplaceFilter<T>::LaplaceFilter(int pLength) : StandardFilter<T>(pLength)
{
    this->length=pLength;
    std::vector<T> mask = std::vector<T>(pLength);
    int half = pLength/2;
    for(int i = 0; i<=half;i++){
        mask[i] = 1;
        mask[pLength-1-i] = 1;
    }
    mask[half]=-(pLength-1);
    this->setMask(mask);
}