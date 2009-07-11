/***********************************************************************
 * Description:  Utility for listing font file metadata.
 * Author:       Joe Halliwell <joe.halliwell@gmail.com>
 * Compile with:
 *    gcc `freetype-config --libs --cflags` -o fontinfo fontinfo.c
 ***********************************************************************/

#include <stdio.h>
#include <ft2build.h>
#include FT_FREETYPE_H

int main(int argc, char** argv)
{
    FT_Library library;
    FT_Face face;
    int error, i;

    if (argc == 1)
    {
        printf("Usage: %s fontfile.ttf [fontfile2.ttf] ...\n", argv[0]);
        return 1;
    }

    error = FT_Init_FreeType(&library);
    if (error)
    {
        fprintf(stderr, "FATAL: Could not initialize freetype library\n");
        return 1;
    }

    for (i = 1; i < argc; i++)
    {
        error = FT_New_Face(library, argv[i], 0, &face);
        if (error)
        {
            fprintf(stderr, "WARNING: Ignoring invalid file %s\n", argv[i]);
            continue;
        }
        if (i != 1)
            printf("-------------------------------------------\n");
        printf("File:\t%s\n",        argv[i]);
        printf("Faces:\t%d\n",       (int) face->num_faces);
        printf("Face:\t%s %s\n",     face->family_name, face->style_name);
        // For other fields see:
        //   http://www.freetype.org/freetype2/docs/reference/ft2-base_interface.html#FT_FaceRec
        FT_Done_Face(face);
    }
    return 0;
}
