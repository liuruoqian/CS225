/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"

using namespace std;

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage> const& theTiles)
{
    /**
     * @todo Implement this function!
     */
/*
    int rows = theSource.getRows();
	int columns = theSource.getColumns();
	//cout<<"reach 19"<<endl;		
	MosaicCanvas * finalMosaic = new MosaicCanvas(rows, columns);
	vector <Point<3> > pixelVector; 
	map <Point<3>, int> indexMap;
	//cout<<"reach 22"<<endl;	
	for(size_t i = 0; i < theTiles.size(); i++)
	{
		RGBAPixel tempPixel = theTiles[i].getAverageColor();
		double setPoint [3];
		setPoint [0]= tempPixel.red;
		setPoint [1]= tempPixel.green;
		setPoint [2]= tempPixel.blue; 
		Point <3> tempPoint(setPoint);
		pixelVector.push_back(tempPoint);
	}
	for(size_t i = 0; i < pixelVector.size(); i++)
	{
		indexMap[pixelVector[i]] = i;
	}
	KDTree <3> sourceTree(pixelVector);
	//<<"reach 37"<<endl;
	for(int rowNumber = 0; rowNumber < rows; rowNumber++)
	{
		for(int columnNumber = 0; columnNumber < columns; columnNumber++)
		{
			RGBAPixel originalPixel = theSource.getRegionColor(rowNumber, columnNumber);
			double pixelArray [3];
			pixelArray [0]= originalPixel.red;
			pixelArray [1]= originalPixel.green;
			pixelArray [2]= originalPixel.blue; 
			Point <3> singlePixel(pixelArray);
			Point <3> properImage = sourceTree.findNearestNeighbor(singlePixel);
			int findIndex = indexMap[properImage];
			TileImage findImage = theTiles[findIndex];			
			finalMosaic->setTile(rowNumber, columnNumber, findImage); 
		}
	}	
	
	return finalMosaic;
	*/

    int row = theSource.getRows();
    int col = theSource.getColumns();
    MosaicCanvas * ret = new MosaicCanvas(row, col);

    std::vector<Point<3>> tilesColor;
    //std::vector<TileImage>::iterator it1;
    //for(it1 = theTiles.begin(); it1 != theTiles.end(); it1++){
    for(size_t i = 0; i < theTiles.size(); i++){
    	RGBAPixel tilecolor = theTiles[i].getAverageColor();
    	double red = tilecolor.red;
    	double green = tilecolor.green;
    	double blue = tilecolor.blue;
    	
    	double arr [3];
    	arr[0] = red;
    	arr[1] = green;
    	arr[2] = blue;
    	Point<3> tileClr(arr);
    	tilesColor.push_back(tileClr);
    }
    //}

    //map can be built in another way !!!

    map<Point<3>, int> colorDict;
    for (size_t i = 0; i < tilesColor.size(); i++){
    	colorDict[tilesColor[i]] = i; // Point-index dict
    }

    KDTree<3> buildMosaic(tilesColor);

    for(int rowIndex = 0; rowIndex < row; rowIndex++){
    	for (int colIndex = 0; colIndex < col; colIndex++){
    		RGBAPixel sourceColor = theSource.getRegionColor(rowIndex, colIndex);
    		double red = sourceColor.red;
    		double green = sourceColor.green;
    		double blue = sourceColor.blue;

    		double arr[3];
    	    arr[0] = red;
    	    arr[1] = green;
    	    arr[2] = blue;
    	    Point<3> tileClr(arr);

    	    Point<3> NNpoint = buildMosaic.findNearestNeighbor(tileClr);
    	    int index = colorDict[NNpoint];
    	    TileImage NNtile = theTiles[index];
    	    ret->setTile(rowIndex, colIndex, NNtile);

    	}
    }


    //return NULL;
    return ret;
    
}

