#pragma once
#include <iostream>


struct Coor
{
	float x, y, z, u, v;
};
struct Indices {
	int i1, i2, i3;
};
Coor *coorVertex = new Coor[512];
Indices* Sequence = new Indices[718];
int load(const char* nfgPath) {
	int temp, normx, normy, normz, bnormx, bnormy, bnormz, tgtx, tgty, tgtz, NrVertices=0, NrIndices;
	float tmp;
	FILE* nfg;
	fopen_s(&nfg, nfgPath, "r");
	if (!nfg) {
		printf("Not NFG file");
		return 0;
	}

	fscanf_s(nfg, "NrVertices:%d", &NrVertices);
	for (int i = 0; i < NrVertices; i++) {
		fscanf_s(nfg, "   %d. pos:[%f, %f, %f]; norm:[%f, %f, %f]; binorm:[%f, %f, %f]; tgt:[%f, %f, %f]; uv:[%f, %f];",
			&temp, &coorVertex[i].x, &coorVertex[i].y, &coorVertex[i].z, &normx, &normy, &normz, &bnormx, &bnormy, &bnormz, &tgtx,&tgty, &tgtz,&coorVertex[i].u, &coorVertex[i].v
		);


		//printf("%d, %f, %f, %f \n", temp,coorVertex[i].x, coorVertex[i].y, coorVertex[i].z);
	}

	fscanf_s(nfg, "\nNrIndices:%d", &NrIndices);
	printf("%d\n", NrIndices);
	for (int i = 0; i < 718; i++) {
		fscanf_s(nfg, "   %d.    %d,    %d,    %d", &temp, &Sequence[i].i1, &Sequence[i].i2, &Sequence[i].i3);


	}
}