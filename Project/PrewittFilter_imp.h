//
// Created by shernand on 12/7/17.
//

template<typename T> PrewittFilter<T>::PrewittFilter() : StandardFilter<T>()
{
    this->setLength(5);
    int pLength = this->length;
    std::vector<T> pMask =this->mask;
    pMask = std::vector<T>(pLength);
    //\todo Find a way to implement the prewitt mas with iota o foreach
    //Fills the mask
    int half = pLength/2;
    for(int i = 0; i<=half;i++){
        pMask[i] = half - i;
        pMask[pLength-1-i] = -(half - i);
    }
    pMask[half]=0;
    this->setMask(pMask);
}
template<typename T> PrewittFilter<T>::PrewittFilter(int pLength) : StandardFilter<T>(pLength)
{
    this->length=pLength;
    std::vector<T> mask = std::vector<T>(pLength);
    int half = pLength/2;
    for(int i = 0; i<=half;i++){
        mask[i] = pLength - 2 * half +i;
        mask[pLength-1-i] = -(pLength - 2 * half+i);
    }
    mask[half]=0;
    this->setMask(mask);
}