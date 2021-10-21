xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 97;
 2.61604;-0.05064;0.02292;,
 2.61604;-1.77886;0.02292;,
 1.93346;-1.77886;-1.62502;,
 1.93346;-0.05064;-1.62502;,
 0.28552;-1.77886;-2.30762;,
 0.28552;-0.05064;-2.30762;,
 -1.36244;-1.77886;-1.62502;,
 -1.36244;-0.05064;-1.62502;,
 -2.04504;-1.77886;0.02292;,
 -2.04504;-0.05064;0.02292;,
 -1.36244;-1.77886;1.67086;,
 -1.36244;-0.05064;1.67086;,
 0.28552;-1.77886;2.35346;,
 0.28552;-0.05064;2.35346;,
 1.93346;-1.77886;1.67086;,
 1.93346;-0.05064;1.67086;,
 2.61604;-1.77886;0.02292;,
 2.61604;-0.05064;0.02292;,
 2.61604;-3.50708;0.02292;,
 1.93346;-3.50708;-1.62502;,
 0.28552;-3.50708;-2.30762;,
 -1.36244;-3.50708;-1.62502;,
 -2.04504;-3.50708;0.02292;,
 -1.36244;-3.50708;1.67086;,
 0.28552;-3.50708;2.35346;,
 1.93346;-3.50708;1.67086;,
 2.61604;-3.50708;0.02292;,
 2.29218;-5.83574;0.02292;,
 1.70444;-5.83574;-1.39600;,
 0.28550;-5.83574;-1.98374;,
 -1.13342;-5.83574;-1.39600;,
 -1.72116;-5.83574;0.02292;,
 -1.13342;-5.83574;1.44184;,
 0.28552;-5.83574;2.02958;,
 1.70444;-5.83574;1.44184;,
 2.29218;-5.83574;0.02292;,
 2.29218;-7.32378;0.02292;,
 1.70444;-7.32378;-1.39600;,
 0.28550;-7.32378;-1.98374;,
 -1.13342;-7.32378;-1.39600;,
 -1.72116;-7.32378;0.02292;,
 -1.13342;-7.32378;1.44184;,
 0.28552;-7.32378;2.02958;,
 1.70444;-7.32378;1.44184;,
 2.29218;-7.32378;0.02292;,
 1.97918;-9.15998;0.02292;,
 1.48310;-9.15998;-1.17468;,
 0.28550;-9.15998;-1.67076;,
 -0.91210;-9.15998;-1.17468;,
 -1.40816;-9.15998;0.02292;,
 -0.91210;-9.15998;1.22052;,
 0.28552;-9.15998;1.71660;,
 1.48310;-9.15998;1.22052;,
 1.97918;-9.15998;0.02292;,
 1.97918;-10.41592;0.02292;,
 1.48310;-10.41592;-1.17468;,
 0.28550;-10.41592;-1.67076;,
 -0.91210;-10.41592;-1.17468;,
 -1.40816;-10.41592;0.02292;,
 -0.91210;-10.41592;1.22052;,
 0.28552;-10.41592;1.71660;,
 1.48310;-10.41592;1.22052;,
 1.97918;-10.41592;0.02292;,
 1.61196;-11.80804;0.02292;,
 1.22346;-11.80804;-0.91502;,
 0.28550;-11.80804;-1.30354;,
 -0.65244;-11.80804;-0.91502;,
 -1.04096;-11.80804;0.02292;,
 -0.65244;-11.80804;0.96086;,
 0.28550;-11.80804;1.34938;,
 1.22346;-11.80804;0.96086;,
 1.61196;-11.80804;0.02292;,
 1.61196;-12.79166;0.02292;,
 1.22346;-12.79166;-0.91502;,
 0.28550;-12.79166;-1.30354;,
 -0.65244;-12.79166;-0.91502;,
 -1.04096;-12.79166;0.02292;,
 -0.65244;-12.79166;0.96086;,
 0.28550;-12.79166;1.34938;,
 1.22346;-12.79166;0.96086;,
 1.61196;-12.79166;0.02292;,
 0.28552;-0.05064;0.02292;,
 0.28552;-0.05064;0.02292;,
 0.28552;-0.05064;0.02292;,
 0.28552;-0.05064;0.02292;,
 0.28552;-0.05064;0.02292;,
 0.28552;-0.05064;0.02292;,
 0.28552;-0.05064;0.02292;,
 0.28552;-0.05064;0.02292;,
 0.28552;-12.79166;0.02292;,
 0.28552;-12.79166;0.02292;,
 0.28552;-12.79166;0.02292;,
 0.28552;-12.79166;0.02292;,
 0.28552;-12.79166;0.02292;,
 0.28552;-12.79166;0.02292;,
 0.28552;-12.79166;0.02292;,
 0.28552;-12.79166;0.02292;;
 
 80;
 4;0,1,2,3;,
 4;3,2,4,5;,
 4;5,4,6,7;,
 4;7,6,8,9;,
 4;9,8,10,11;,
 4;11,10,12,13;,
 4;13,12,14,15;,
 4;15,14,16,17;,
 4;1,18,19,2;,
 4;2,19,20,4;,
 4;4,20,21,6;,
 4;6,21,22,8;,
 4;8,22,23,10;,
 4;10,23,24,12;,
 4;12,24,25,14;,
 4;14,25,26,16;,
 4;18,27,28,19;,
 4;19,28,29,20;,
 4;20,29,30,21;,
 4;21,30,31,22;,
 4;22,31,32,23;,
 4;23,32,33,24;,
 4;24,33,34,25;,
 4;25,34,35,26;,
 4;27,36,37,28;,
 4;28,37,38,29;,
 4;29,38,39,30;,
 4;30,39,40,31;,
 4;31,40,41,32;,
 4;32,41,42,33;,
 4;33,42,43,34;,
 4;34,43,44,35;,
 4;36,45,46,37;,
 4;37,46,47,38;,
 4;38,47,48,39;,
 4;39,48,49,40;,
 4;40,49,50,41;,
 4;41,50,51,42;,
 4;42,51,52,43;,
 4;43,52,53,44;,
 4;45,54,55,46;,
 4;46,55,56,47;,
 4;47,56,57,48;,
 4;48,57,58,49;,
 4;49,58,59,50;,
 4;50,59,60,51;,
 4;51,60,61,52;,
 4;52,61,62,53;,
 4;54,63,64,55;,
 4;55,64,65,56;,
 4;56,65,66,57;,
 4;57,66,67,58;,
 4;58,67,68,59;,
 4;59,68,69,60;,
 4;60,69,70,61;,
 4;61,70,71,62;,
 4;63,72,73,64;,
 4;64,73,74,65;,
 4;65,74,75,66;,
 4;66,75,76,67;,
 4;67,76,77,68;,
 4;68,77,78,69;,
 4;69,78,79,70;,
 4;70,79,80,71;,
 3;81,0,3;,
 3;82,3,5;,
 3;83,5,7;,
 3;84,7,9;,
 3;85,9,11;,
 3;86,11,13;,
 3;87,13,15;,
 3;88,15,17;,
 3;89,73,72;,
 3;90,74,73;,
 3;91,75,74;,
 3;92,76,75;,
 3;93,77,76;,
 3;94,78,77;,
 3;95,79,78;,
 3;96,80,79;;
 
 MeshMaterialList {
  1;
  80;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0;;
  Material {
   1.000000;1.000000;1.000000;1.000000;;
   0.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  70;
  0.000000;1.000000;0.000000;,
  1.000000;0.000000;0.000000;,
  0.707110;0.000000;-0.707103;,
  0.000002;0.000000;-1.000000;,
  -0.707105;0.000000;-0.707108;,
  -1.000000;0.000000;0.000000;,
  -0.707105;0.000000;0.707108;,
  0.000002;0.000000;1.000000;,
  0.707110;0.000000;0.707103;,
  1.000000;0.000000;0.000000;,
  0.707110;0.000000;-0.707103;,
  0.000002;0.000000;-1.000000;,
  -0.707105;0.000000;-0.707108;,
  -1.000000;0.000000;0.000000;,
  0.997610;-0.069090;0.000000;,
  0.705419;-0.069092;-0.705415;,
  0.000001;-0.069092;-0.997610;,
  -0.705416;-0.069092;-0.705418;,
  -0.997610;-0.069092;0.000000;,
  -0.705415;-0.069092;0.705419;,
  0.000002;-0.069092;0.997610;,
  0.705420;-0.069091;0.705414;,
  0.997610;-0.069090;0.000000;,
  0.705417;-0.069092;-0.705418;,
  -0.000001;-0.069092;-0.997610;,
  -0.705417;-0.069092;-0.705417;,
  -0.997610;-0.069092;0.000000;,
  -0.705415;-0.069092;0.705419;,
  0.000003;-0.069092;0.997610;,
  0.705418;-0.069091;0.705416;,
  0.996431;-0.084408;-0.000000;,
  0.704582;-0.084406;-0.704585;,
  -0.000002;-0.084403;-0.996432;,
  -0.704585;-0.084404;-0.704582;,
  -0.996431;-0.084406;0.000000;,
  -0.704583;-0.084404;0.704584;,
  0.000003;-0.084403;0.996432;,
  0.704584;-0.084406;0.704583;,
  0.996431;-0.084408;-0.000000;,
  0.704583;-0.084405;-0.704584;,
  -0.000001;-0.084403;-0.996432;,
  -0.704587;-0.084404;-0.704580;,
  -0.996431;-0.084405;0.000000;,
  -0.704585;-0.084404;0.704582;,
  0.000005;-0.084403;0.996432;,
  0.704585;-0.084405;0.704582;,
  0.991657;-0.128901;-0.000000;,
  0.701209;-0.128902;-0.701207;,
  -0.000001;-0.128905;-0.991657;,
  -0.701211;-0.128902;-0.701204;,
  -0.991657;-0.128901;-0.000000;,
  -0.701210;-0.128902;0.701205;,
  0.000003;-0.128905;0.991657;,
  0.701210;-0.128902;0.701205;,
  0.991657;-0.128901;0.000000;,
  0.701210;-0.128902;-0.701205;,
  -0.000003;-0.128904;-0.991657;,
  -0.701209;-0.128902;-0.701206;,
  -0.991657;-0.128902;-0.000000;,
  -0.701208;-0.128902;0.701207;,
  -0.000001;-0.128905;0.991657;,
  0.701211;-0.128903;0.701204;,
  1.000000;0.000000;0.000000;,
  -0.000004;0.000000;-1.000000;,
  -0.707107;0.000000;-0.707107;,
  -1.000000;0.000000;0.000000;,
  -0.707107;0.000000;0.707107;,
  -0.000004;0.000000;1.000000;,
  0.707110;0.000000;0.707103;,
  0.000000;-1.000000;-0.000000;;
  80;
  4;1,9,10,2;,
  4;2,10,11,3;,
  4;3,11,12,4;,
  4;4,12,13,5;,
  4;5,13,6,6;,
  4;6,6,7,7;,
  4;7,7,8,8;,
  4;8,8,9,1;,
  4;9,14,15,10;,
  4;10,15,16,11;,
  4;11,16,17,12;,
  4;12,17,18,13;,
  4;13,18,19,6;,
  4;6,19,20,7;,
  4;7,20,21,8;,
  4;8,21,14,9;,
  4;14,22,23,15;,
  4;15,23,24,16;,
  4;16,24,25,17;,
  4;17,25,26,18;,
  4;18,26,27,19;,
  4;19,27,28,20;,
  4;20,28,29,21;,
  4;21,29,22,14;,
  4;22,30,31,23;,
  4;23,31,32,24;,
  4;24,32,33,25;,
  4;25,33,34,26;,
  4;26,34,35,27;,
  4;27,35,36,28;,
  4;28,36,37,29;,
  4;29,37,30,22;,
  4;30,38,39,31;,
  4;31,39,40,32;,
  4;32,40,41,33;,
  4;33,41,42,34;,
  4;34,42,43,35;,
  4;35,43,44,36;,
  4;36,44,45,37;,
  4;37,45,38,30;,
  4;38,46,47,39;,
  4;39,47,48,40;,
  4;40,48,49,41;,
  4;41,49,50,42;,
  4;42,50,51,43;,
  4;43,51,52,44;,
  4;44,52,53,45;,
  4;45,53,46,38;,
  4;46,54,55,47;,
  4;47,55,56,48;,
  4;48,56,57,49;,
  4;49,57,58,50;,
  4;50,58,59,51;,
  4;51,59,60,52;,
  4;52,60,61,53;,
  4;53,61,54,46;,
  4;54,62,2,55;,
  4;55,2,63,56;,
  4;56,63,64,57;,
  4;57,64,65,58;,
  4;58,65,66,59;,
  4;59,66,67,60;,
  4;60,67,68,61;,
  4;61,68,62,54;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;69,69,69;,
  3;69,69,69;,
  3;69,69,69;,
  3;69,69,69;,
  3;69,69,69;,
  3;69,69,69;,
  3;69,69,69;,
  3;69,69,69;;
 }
 MeshTextureCoords {
  97;
  0.000000;0.000000;,
  0.000000;0.125000;,
  0.125000;0.125000;,
  0.125000;0.000000;,
  0.250000;0.125000;,
  0.250000;0.000000;,
  0.375000;0.125000;,
  0.375000;0.000000;,
  0.500000;0.125000;,
  0.500000;0.000000;,
  0.625000;0.125000;,
  0.625000;0.000000;,
  0.750000;0.125000;,
  0.750000;0.000000;,
  0.875000;0.125000;,
  0.875000;0.000000;,
  1.000000;0.125000;,
  1.000000;0.000000;,
  0.000000;0.250000;,
  0.125000;0.250000;,
  0.250000;0.250000;,
  0.375000;0.250000;,
  0.500000;0.250000;,
  0.625000;0.250000;,
  0.750000;0.250000;,
  0.875000;0.250000;,
  1.000000;0.250000;,
  0.000000;0.375000;,
  0.125000;0.375000;,
  0.250000;0.375000;,
  0.375000;0.375000;,
  0.500000;0.375000;,
  0.625000;0.375000;,
  0.750000;0.375000;,
  0.875000;0.375000;,
  1.000000;0.375000;,
  0.000000;0.500000;,
  0.125000;0.500000;,
  0.250000;0.500000;,
  0.375000;0.500000;,
  0.500000;0.500000;,
  0.625000;0.500000;,
  0.750000;0.500000;,
  0.875000;0.500000;,
  1.000000;0.500000;,
  0.000000;0.625000;,
  0.125000;0.625000;,
  0.250000;0.625000;,
  0.375000;0.625000;,
  0.500000;0.625000;,
  0.625000;0.625000;,
  0.750000;0.625000;,
  0.875000;0.625000;,
  1.000000;0.625000;,
  0.000000;0.750000;,
  0.125000;0.750000;,
  0.250000;0.750000;,
  0.375000;0.750000;,
  0.500000;0.750000;,
  0.625000;0.750000;,
  0.750000;0.750000;,
  0.875000;0.750000;,
  1.000000;0.750000;,
  0.000000;0.875000;,
  0.125000;0.875000;,
  0.250000;0.875000;,
  0.375000;0.875000;,
  0.500000;0.875000;,
  0.625000;0.875000;,
  0.750000;0.875000;,
  0.875000;0.875000;,
  1.000000;0.875000;,
  0.000000;1.000000;,
  0.125000;1.000000;,
  0.250000;1.000000;,
  0.375000;1.000000;,
  0.500000;1.000000;,
  0.625000;1.000000;,
  0.750000;1.000000;,
  0.875000;1.000000;,
  1.000000;1.000000;,
  0.062500;0.000000;,
  0.187500;0.000000;,
  0.312500;0.000000;,
  0.437500;0.000000;,
  0.562500;0.000000;,
  0.687500;0.000000;,
  0.812500;0.000000;,
  0.937500;0.000000;,
  0.062500;1.000000;,
  0.187500;1.000000;,
  0.312500;1.000000;,
  0.437500;1.000000;,
  0.562500;1.000000;,
  0.687500;1.000000;,
  0.812500;1.000000;,
  0.937500;1.000000;;
 }
}
