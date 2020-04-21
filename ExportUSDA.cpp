#include "ExportUSDA.h"
#include "FloatMath.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

namespace exportusda
{

bool exportUSDA(uint32_t vcount,
    uint32_t tcount,
    const float *vertices,
    const uint32_t *indices,
    const char *fname)
{
    bool ret = false;

    FILE *fph = fopen(fname,"wb");
    if ( fph )
    {
        fprintf(fph, "#usda 1.0\n");
        fprintf(fph, "(\n");
        fprintf(fph, "    customLayerData = {\n");
        fprintf(fph, "        dictionary cameraSettings = {\n");
        fprintf(fph, "            dictionary Front = {\n");
        fprintf(fph, "                double3 position = (0, 0, 1000)\n");
        fprintf(fph, "                double radius = 500\n");
        fprintf(fph, "                double3 target = (0, 0, 0)\n");
        fprintf(fph, "            }\n");
        fprintf(fph, "            dictionary Perspective = {\n");
        fprintf(fph, "                double3 position = (179.45975233213068, 179.45975233213073, 229.45975233213053)\n");
        fprintf(fph, "                double radius = 310.8334089529776\n");
        fprintf(fph, "                double3 target = (0, 0, 50)\n");
        fprintf(fph, "            }\n");
        fprintf(fph, "            dictionary Right = {\n");
        fprintf(fph, "                double3 position = (-1000, 0, -2.220446049250313e-13)\n");
        fprintf(fph, "                double radius = 500\n");
        fprintf(fph, "                double3 target = (0, 0, 0)\n");
        fprintf(fph, "            }\n");
        fprintf(fph, "            dictionary Top = {\n");
        fprintf(fph, "                double3 position = (-8.659560562354932e-14, 1000, 2.220446049250313e-13)\n");
        fprintf(fph, "                double radius = 500\n");
        fprintf(fph, "                double3 target = (0, 0, 0)\n");
        fprintf(fph, "            }\n");
        fprintf(fph, "            string boundCamera = \"/OmniverseKit_Persp\"\n");
        fprintf(fph, "        }\n");
        fprintf(fph, "        dictionary renderSettings = {\n");
        fprintf(fph, "        }\n");
        fprintf(fph, "    }\n");
        fprintf(fph, "    defaultPrim = \"Root\"\n");
        fprintf(fph, "    metersPerUnit = 0.009999999776482582\n");
        fprintf(fph, ")\n");
        fprintf(fph, "\n");
        fprintf(fph, "def Xform \"Root\" (\n");
        fprintf(fph, "    kind = \"model\"\n");
        fprintf(fph, ")\n");
        fprintf(fph, "{\n");
        fprintf(fph, "    def Scope \"Looks\"\n");
        fprintf(fph, "    {\n");
        fprintf(fph, "        def Material \"DefaultMaterial\"\n");
        fprintf(fph, "        {\n");
        fprintf(fph, "            token outputs:surface.connect = </Root/Looks/DefaultMaterial/DefaultMaterial.outputs:out>\n");
        fprintf(fph, "\n");
        fprintf(fph, "            def Shader \"DefaultMaterial\"\n");
        fprintf(fph, "            {\n");
        fprintf(fph, "                uniform token info:implementationSource = \"sourceAsset\"\n");
        fprintf(fph, "                uniform asset info:mdl:sourceAsset = @omni:/Users/jratcliff/cube/materials/DefaultMaterial.mdl@\n");
        fprintf(fph, "                uniform token info:mdl:sourceAsset:subIdentifier = \".::materials::DefaultMaterial::DefaultMaterial\"\n");
        fprintf(fph, "                token outputs:out\n");
        fprintf(fph, "            }\n");
        fprintf(fph, "        }\n");
        fprintf(fph, "    }\n");


        fprintf(fph,"def Mesh \"defaultobject\" {\n");

        float bmin[3];
        float bmax[3];
        FLOAT_MATH::fm_initMinMax(bmin,bmax);
        for (uint32_t i=0; i<vcount; i++)
        {
            const float *p = &vertices[i*3];
            FLOAT_MATH::fm_minmax(p,bmin,bmax);
        }
        fprintf(fph," float3[] extent = [(%0.9f, %0.9f, %0.9f), (%0.9f, %0.9f, %0.9f)]\n", bmin[0],bmin[1],bmin[2],bmax[0],bmax[1],bmax[2]);

        fprintf(fph," int[] faceVertexCounts = [");

        uint32_t count=0;
        for (uint32_t i=0; i<tcount; i++)
        {
            fprintf(fph,"%d", 3 );
            if ( (i+1) < tcount )
            {
                fprintf(fph,", ");
            }
            count++;
            if ( count == 5  )
            {
                count = 0;
                fprintf(fph,"\n ");
            }
        }

        fprintf(fph,"]\n");

        fprintf(fph, " int[] faceVertexIndices = [");
        count = 0;
        uint32_t indexCount = tcount*3;

        for (uint32_t i = 0; i < indexCount; i++)
        {
            fprintf(fph, "%d", indices[i]);
            if ((i + 1) < indexCount)
            {
                fprintf(fph, ", ");
            }
            count++;
            if (count == 5)
            {
                count = 0;
                fprintf(fph, "\n ");
            }
        }
        fprintf(fph,"]\n");

        fprintf(fph,"rel material:binding = </Root/Looks/DefaultMaterial>\n");

        fprintf(fph, " point3f[] points = [");
        count = 0;

        for (uint32_t i = 0; i < vcount; i++)
        {
            const float *p = &vertices[i*3];
            fprintf(fph, "(%0.9f, %0.9f, %0.9f)", p[0], p[1], p[2]);
            if ((i + 1) < vcount)
            {
                fprintf(fph, ", ");
            }
            count++;
            if (count == 5)
            {
                count = 0;
                fprintf(fph, "\n ");
            }
        }

        fprintf(fph, "]\n");

        fprintf(fph, "uniform token subdivisionScheme = \"none\"\n");
        fprintf(fph, "matrix4d xformOp:transform = ((1, 0, 0, 0), (0, 1, 0, 0), (0, 0, 1, 0), (0, 0, 0, 1))\n");
        fprintf(fph, "uniform token[] xformOpOrder = [\"xformOp:transform\"]\n");

        fprintf(fph,"}\n");

        fprintf(fph,"}\n");
        fclose(fph);
        ret = true;
    }
    return ret;
}


}
