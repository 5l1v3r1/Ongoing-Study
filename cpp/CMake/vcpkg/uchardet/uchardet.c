// https://cgit.freedesktop.org/uchardet/uchardet/tree/src/tools/uchardet.cpp

/* ***** BEGIN LICENSE BLOCK *****
 * Version: MPL 1.1/GPL 2.0/LGPL 2.1
 *
 * The contents of this file are subject to the Mozilla Public License Version
 * 1.1 (the "License"); you may not use this file except in compliance with
 * the License. You may obtain a copy of the License at
 * http://www.mozilla.org/MPL/
 *
 * Software distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
 * for the specific language governing rights and limitations under the
 * License.
 *
 * The Original Code is Mozilla Universal charset detector code.
 *
 * The Initial Developer of the Original Code is
 * Netscape Communications Corporation.
 * Portions created by the Initial Developer are Copyright (C) 2001
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):
 *          BYVoid <byvoid.kcp@gmail.com>
 *
 * Alternatively, the contents of this file may be used under the terms of
 * either the GNU General Public License Version 2 or later (the "GPL"), or
 * the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
 * in which case the provisions of the GPL or the LGPL are applicable instead
 * of those above. If you wish to allow use of your version of this file only
 * under the terms of either the GPL or the LGPL, and not to allow others to
 * use your version of this file under the terms of the MPL, indicate your
 * decision by deleting the provisions above and replace them with the notice
 * and other provisions required by the GPL or the LGPL. If you do not delete
 * the provisions above, a recipient may use your version of this file under
 * the terms of any one of the MPL, the GPL or the LGPL.
 *
 * ***** END LICENSE BLOCK ***** */

#include <stddef.h>
#include <stdio.h>

#include <uchardet/uchardet.h>


#define BUFFER_SIZE 65536

char buffer[BUFFER_SIZE];


void detect(FILE * fp)
{
    const char *charset = NULL;

    uchardet_t handle = uchardet_new();

    while (!feof(fp))
    {
        size_t len = fread(buffer, 1, BUFFER_SIZE, fp);
        int retval = uchardet_handle_data(handle, buffer, len);
        if (retval != 0)
        {
            fprintf(stderr, "Handle data error.\n");
            exit(1);
        }
    }
    uchardet_data_end(handle);

    charset = uchardet_get_charset(handle);
    if (*charset)
        printf("%s\n", charset);
    else
        printf("unknown\n");
    
    uchardet_delete(handle);
}


int main(int argc, char ** argv)
{
    FILE * f = stdin;
    int error_seen = 0;
    if (argc < 2)
    {
        // No file arg, use stdin by default
        detect(f);
    }
    
    for (int i = 1; i < argc; i++)
    {
        const char *filename = argv[i];
        f = fopen(filename, "r");
        if (f == NULL)
        {
            perror(filename);
            error_seen = 1;
            continue;
        }
        if (argc > 2)
        {
            printf("%s: ", filename);
        }
        detect(f);
    }

    return error_seen;
}