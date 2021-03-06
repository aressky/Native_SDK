// This file was created by Filewrap 1.2
// Little endian mode
// DO NOT EDIT

#include "../PVRTMemoryFileSystem.h"

// using 32 bit to guarantee alignment.
#ifndef A32BIT
 #define A32BIT static const unsigned int
#endif

// ******** Start: MagicLanternShaders.pfx ********

// File data
static const char _MagicLanternShaders_pfx[] = 
	"////////////////////////////////////////////////////////////////////////////////////\n"
	"// MagicLantern PFX file.\n"
	"// \n"
	"// This file contains two shaders sets.\n"
	"// The first one transform and light the vertices using a coloured point \n"
	"// light with diffuse and specular components. It also projects a cubemap\n"
	"// texture containing the light-map which is blended (modulation) with the base \n"
	"// texture.\n"
	"// The second set is just to draw the cubemap on the sphere with a diffuse colour.\n"
	"////////////////////////////////////////////////////////////////////////////////////\n"
	"\n"
	"[HEADER]\t\n"
	"\tVERSION\t\t00.00.00.00\t\n"
	"\tDESCRIPTION MagicLantern: Dynamic Lighting example. \t\n"
	"\tCOPYRIGHT\tImagination Technologies Ltd.\t\n"
	"[/HEADER]\n"
	"\n"
	"// Texture description\n"
	"// For cubemap always use clamp to edge to avoid wrapping artefacts\n"
	"// that might show the seams of the textures. \n"
	"[TEXTURE]\n"
	"\tNAME\t\t\tlantern\n"
	"\tPATH\t\t\tLanternCubemap.pvr\n"
	"\tMINIFICATION\tLINEAR\n"
	"\tMAGNIFICATION\tLINEAR\n"
	"\tMIPMAP\t\t\tNEAREST\n"
	"\tWRAP_S\t\t\tCLAMP\n"
	"\tWRAP_T\t\t\tCLAMP\n"
	"[/TEXTURE]\n"
	"[TEXTURE]\n"
	"\tNAME\t\t\tfloor\n"
	"\tPATH\t\t\tFloor.pvr\n"
	"\tMINIFICATION\tLINEAR\n"
	"\tMAGNIFICATION\tLINEAR\n"
	"\tMIPMAP\t\t\tNEAREST\n"
	"\tWRAP_S\t\t\tREPEAT\n"
	"\tWRAP_T\t\t\tREPEAT\n"
	"[/TEXTURE]\n"
	"[TEXTURE]\n"
	"\tNAME\t\t\tmarble\n"
	"\tPATH\t\t\tMarble.pvr\n"
	"\tMINIFICATION\tLINEAR\n"
	"\tMAGNIFICATION\tLINEAR\n"
	"\tMIPMAP\t\t\tNEAREST\n"
	"\tWRAP_S\t\t\tREPEAT\n"
	"\tWRAP_T\t\t\tREPEAT\n"
	"[/TEXTURE]\n"
	"\t\n"
	"// Projected light-map vertex shader\n"
	"[VERTEXSHADER]\n"
	"\tNAME myProjectionVSh\n"
	"\t[GLSL_CODE]\n"
	"\t\tattribute highp   vec3  inVertex;\n"
	"\t\tattribute mediump vec3  inNormal;\n"
	"\t\tattribute mediump vec2  inTexCoord;\n"
	"\n"
	"\t\tuniform highp mat4  MVPMatrix;\n"
	"\t\tuniform highp mat3  ModelIT;\n"
	"\t\tuniform highp vec3  LightPosition;\n"
	"\t\tuniform highp vec3 \tLightColor;\n"
	"\n"
	"\t\tvarying mediump vec4  DiffuseLight;\n"
	"\t\tvarying mediump vec4  SpecularLight;\n"
	"\t\tvarying mediump vec2  TexCoord;\n"
	"\t\tvarying mediump vec3  ReflectDir;\n"
	"\n"
	"\t\tconst highp float  cShininess = 32.0;\n"
	"\n"
	"\n"
	"\t\tvoid main()\n"
	"\t\t{\n"
	"\t\t\t// LIGHTING\n"
	"\t\t\t// This demo uses point light with specular using a  \n"
	"\t\t\t// simplified algorithm without half-vector.\n"
	"\t\t\t// For a complete implementation of point light, please, \n"
	"\t\t\t// check our ComplexLighting training course.\t\n"
	"\t\t\t\n"
	"\t\t\t// Get the direction vector from the position of the light\n"
	"\t\t\t// to the vertex (it has to be normalised for the dot product to work).\n"
	"\t\t\thighp vec3 lightDir = -normalize(inVertex - LightPosition);\n"
	"\n"
	"\t\t\t// Calculate smooth-shading as the cosine between the light angle \n"
	"\t\t\t// and the normal at that vertex (i.e. dot product)\n"
	"\t\t\t// The clamping will give us 1.0 (full light) when the normal and the \n"
	"\t\t\t// light direction coincide and 0.0 when they are at 90 degrees\t\n"
	"\t\t\thighp float Intensity = max(dot(inNormal, lightDir), 0.0);\t\n"
	"\t\t\t\n"
	"\t\t\t// Calculate now the specular component\n"
	"\t\t\tSpecularLight = pow(Intensity, cShininess) * vec4(LightColor,1.0);\n"
	"\t\t\tDiffuseLight = Intensity * vec4(LightColor,1.0);\t\n"
	"\t\t\t\t\n"
	"\t\t\t// The direction from the light position to the vertex is transformed\n"
	"\t\t\t// with the inverse-transpose of the same matrix used to transform\n"
	"\t\t\t// the sphere. The resulting vector will be used to map into the\n"
	"\t\t\t// cubemap texture with our lightmap.\n"
	"\t\t\tReflectDir =  lightDir * ModelIT;\n"
	"\n"
	"\t\t\t// Transform position\n"
	"\t\t\tgl_Position = MVPMatrix * vec4(inVertex, 1.0);\n"
	"\t\t\t\n"
	"\t\t\t// Pass through texcoords\n"
	"\t\t\tTexCoord = inTexCoord;\n"
	"\t\t}\n"
	"\t[/GLSL_CODE]\n"
	"[/VERTEXSHADER]\n"
	"\n"
	"// Projected light-map fragment shader\n"
	"[FRAGMENTSHADER]\n"
	"\tNAME myProjectionFSh\n"
	"\t[GLSL_CODE]\n"
	"\t\t\n"
	"\n"
	"\t\tuniform sampler2D  sTexture;\n"
	"\t\tuniform samplerCube sLightMap;\n"
	"\t\t\n"
	"\t\tvarying mediump vec3  ReflectDir;\n"
	"\t\tvarying mediump vec2  TexCoord;\n"
	"\t\t\n"
	"\t\tvarying lowp    vec4  DiffuseLight;\n"
	"\t\tvarying lowp    vec4  SpecularLight;\n"
	"\n"
	"\t\tvoid main()\n"
	"\t\t{\n"
	"\t\t\t// Get the lightmap colour\n"
	"\t\t\tlowp vec4 lightMap = (textureCube(sLightMap, ReflectDir));\n"
	"\n"
	"\t\t\t// Compose the final colour modulating the base texture with the lightmap and multiplying by the diffuse colour.\n"
	"\t\t\t// The specular component is added at the end.\n"
	"\t\t\tgl_FragColor = texture2D(sTexture,TexCoord)*lightMap * DiffuseLight + SpecularLight;\n"
	"\t\t}\n"
	"\t[/GLSL_CODE]\n"
	"[/FRAGMENTSHADER]\n"
	"\n"
	"// Simple textured sphere vertex shader\n"
	"[VERTEXSHADER]\n"
	"\tNAME \t\tSphereVertexShader\n"
	"\n"
	"\t// LOAD GLSL AS CODE\n"
	"\t[GLSL_CODE]\n"
	"\t\tattribute highp   vec3  inVertex;\n"
	"\t\tattribute mediump vec3  inNormal;\n"
	"\t\tuniform highp   mat4  MVPMatrix;\n"
	"\t\tvarying mediump vec3   ReflectDir;\n"
	"\n"
	"\t\tvoid main()\n"
	"\t\t{\n"
	"\t\t\t// Transfotm position\n"
	"\t\t\tgl_Position = MVPMatrix * vec4(inVertex, 1.0);\n"
	"\n"
	"\t\t\t// Pass the inverse of the normal (to map into the cubamap)\n"
	"\t\t\tReflectDir = -inNormal;\n"
	"\t\t}\n"
	"\t[/GLSL_CODE]\n"
	"[/VERTEXSHADER]\n"
	"\n"
	"// Simple textured sphere fragment shader\n"
	"[FRAGMENTSHADER] \n"
	"\tNAME \t\tSphereFragmentShader \n"
	"\n"
	"\t// LOAD GLSL AS CODE\n"
	"\t[GLSL_CODE]\n"
	"\t\tuniform samplerCube sLightMap;\n"
	"\t\tuniform lowp  vec3  LightColor;\n"
	"\t\tvarying mediump vec3 ReflectDir;\n"
	"\n"
	"\t\tvoid main()\n"
	"\t\t{\n"
	"\t\t\t// Final colour is the modulaion of the base texture with the diffuse colour.\n"
	"\t\t\tgl_FragColor = (textureCube(sLightMap, ReflectDir)) * vec4(LightColor, 1.0);\n"
	"\t\t}\n"
	"\t[/GLSL_CODE]\n"
	"[/FRAGMENTSHADER]\n"
	"\n"
	"[EFFECT]\n"
	"\tNAME MarbleProjection\n"
	"\n"
	"\tATTRIBUTE \tinVertex\tPOSITION\n"
	"\tATTRIBUTE\tinNormal\tNORMAL\n"
	"\tATTRIBUTE\tinTexCoord\tUV\n"
	"\t\n"
	"\tUNIFORM MVPMatrix WORLDVIEWPROJECTION\n"
	"\tUNIFORM ModelIT WORLDIT\n"
	"\tUNIFORM LightPosition LIGHTPOSWORLD\n"
	"\tUNIFORM LightColor LIGHTCOLOR\n"
	"\t\n"
	"\tUNIFORM sTexture TEXTURE0\n"
	"\tUNIFORM sLightMap TEXTURE1\n"
	"\tTEXTURE 0 marble\n"
	"\tTEXTURE 1 lantern\n"
	"\n"
	"\tVERTEXSHADER myProjectionVSh\n"
	"\tFRAGMENTSHADER myProjectionFSh\n"
	"[/EFFECT]\n"
	"\n"
	"[EFFECT]\n"
	"\tNAME FloorProjection\n"
	"\n"
	"\tATTRIBUTE \tinVertex\tPOSITION\n"
	"\tATTRIBUTE\tinNormal\tNORMAL\n"
	"\tATTRIBUTE\tinTexCoord\tUV\n"
	"\t\n"
	"\tUNIFORM MVPMatrix WORLDVIEWPROJECTION\n"
	"\tUNIFORM ModelIT WORLDIT\n"
	"\tUNIFORM LightPosition LIGHTPOSWORLD\n"
	"\tUNIFORM LightColor LIGHTCOLOR\n"
	"\t\n"
	"\tUNIFORM sTexture TEXTURE0\n"
	"\tUNIFORM sLightMap TEXTURE1\n"
	"\tTEXTURE 0 floor\n"
	"\tTEXTURE 1 lantern\n"
	"\n"
	"\tVERTEXSHADER myProjectionVSh\n"
	"\tFRAGMENTSHADER myProjectionFSh\n"
	"[/EFFECT]\n"
	"\n"
	"[EFFECT]\n"
	"\tNAME Sphere\n"
	"\n"
	"\tATTRIBUTE \tinVertex\tPOSITION\n"
	"\tATTRIBUTE\tinNormal\tNORMAL\n"
	"\t\n"
	"\tUNIFORM MVPMatrix WORLDVIEWPROJECTION\n"
	"\tUNIFORM LightColor LIGHTCOLOR\n"
	"\tUNIFORM sLightMap TEXTURE0\n"
	"\tTEXTURE 0 lantern\n"
	"\n"
	"\tVERTEXSHADER SphereVertexShader\n"
	"\tFRAGMENTSHADER SphereFragmentShader\n"
	"[/EFFECT]";

// Register MagicLanternShaders.pfx in memory file system at application startup time
static CPVRTMemoryFileSystem RegisterFile_MagicLanternShaders_pfx("MagicLanternShaders.pfx", _MagicLanternShaders_pfx, 5996);

// ******** End: MagicLanternShaders.pfx ********

