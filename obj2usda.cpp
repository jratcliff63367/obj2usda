#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "wavefront.h"
#include "ExportUSDA.h"

char *lastDot(char *scan)
{
    char *ret = nullptr;

    while ( *scan )
    {
        if ( *scan == '.' )
        {
            ret = scan;
        }
        scan++;
    }
    return ret;
}

int main(int argc,const char **argv)
{
	if ( argc < 2 )
	{
		printf("Usage: obj2usda <wavefrontobjfile> (options)\n");
        printf("-scale <scaleInputMesh>\n");
        printf("-center <true/false>\n");
	}
    else
    {
        bool center = false;
        float scale = 1;
        const char *fname = argv[1];
        for (int i=2; i<argc; i+=2)
        {
            if ( (i+1) < argc )
            {
                const char *key = argv[i];
                const char *value = argv[i+1];
                if ( strcmp(key,"-scale") == 0 )
                {
                    scale = float(atof(value));
                    if ( scale < 0.00001 )
                    {
                        scale = 1;
                    }
                }
                else if ( strcmp(key,"-center") == 0 )
                {
                    center = strcmp(value,"true") == 0;
                }
            }
        }
        WavefrontObj w;
        uint32_t tcount = w.loadObj(fname);
        if ( tcount )
        {
            WavefrontObj w2;
            w.deepCopyScale(w2,scale,center,0);
            printf("Loaded WavefrontOBJ:%s with %d triangles.\n", fname, tcount );

            char temp[2048];
            strncpy(temp,fname,sizeof(temp));
            char *dot = lastDot(temp);
            if ( dot )
            {
                *dot = 0;
                strncat(temp,".usda",sizeof(temp));
                printf("Saving triangle mesh as USDA file:%s\n", temp );
                exportusda::exportUSDA(w2.mVertexCount,w2.mTriCount,w2.mVertices,w2.mIndices,temp);
            }
            else
            {
                printf("Expecting a post fix like '.obj' in soure file:%s\n", fname );
            }
        }
        else
        {
            printf("No triangles found in the wavefront OBJ file:%s\n", fname);
        }
    }

	return 0;
}
