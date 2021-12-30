/*
  Smartversion
  Copyright (c) Gilles Vollant, 2002-2022

  https://github.com/gvollant/smartversion
  https://www.smartversion.com/
  https://www.winimage.com/

 This source code is licensed under MIT licence.


  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in
  all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
  THE SOFTWARE.
*/

DECLARE_DFHANDLE(DFSFILEWRAP);




/****************************************************************************/
/****************************************************************************/

/*
szMagicText : Texte de pr�sentation du format DFS (avec URL). DfCrcMagicText est le CRC32 de ce texte. (on s'inspirera du debut du PNG pour prot�ger contre les accidents de conversion bin/ascii)
dfMagic : un code Magic 'GVDF'.
dfVersionForCreate : permet de conna�tre la version utilis�e pour cr�er le fichier.
dfVersionNeeded : version n�cessaire � l'ouverture du fichier.
dfsTotalSize : taille du fichier DFS hors en-t�te. (o� 0 pour DFSINFOBEGIN dans le cas stream)
dfsThisFileSize : taille du fichier volume DFS courant (o� 0 pour DFSINFOBEGIN dans le cas stream). Diff�rent de dfsTotalSize uniquement pour le multivolume.
dfsThisVolumeNumber : num�ro du fichier courant dans l'ordre des volumes. (0 pour le cas stream, 1 pour le cas illimit�)
dfsTotalNumberOfVolume : nombre total de volume (0 pour le cas stream, 1 pour le cas taille illimit�)
dfsVolumeSize : taille d'un volume (0 pour le cas stream ou illimit�).
*/


typedef struct
{
  dfuLong32 sizeStruct;
  dfuLong32 dfStatus;
  const void *filename;         /* filename or other info for open callback */
}
DFSFILEINFOPARAMINTERNAL;

DFSFILEWRAP DfsOpenFile(DFSFILEINFOPARAMINTERNAL DfsFileParam, H_ERROR_INFO* pei);
/*
Ouvre un fichier DFS.
Param�tres :
dfsStatus : Voir DfsGetStatus
Valeur de retour : handle du Fichier DFS
*/

dfuLong32 DfsFlushWriteFile(DFSFILEWRAP dfsFileWrap,H_ERROR_INFO* pei);
/*
Flush les donn�e du fichier DFS.
Param�tres :
DfsFileWrap :   Handle du fichier DFS
Valeur de retour : 0
*/


dfuLong32 DfsCloseFile(DFSFILEWRAP dfsFileWrap,H_ERROR_INFO* pei);
/*
Ferme un fichier DFS.
Param�tres :
DfsFileWrap :   Handle du fichier DFS
Valeur de retour : 0
*/

dfuLong32 DfsGetStatus(DFSFILEWRAP dfsFileWrap,H_ERROR_INFO* pei);
/*
Retourne les flag permettant de savoir ce qui est possible avec le fichier.
Param�tres :
DfsFileWrap :   Handle du fichier DFS
Valeur de retour : Combinaison des valeurs suivantes
DFS_STREAM :    implique qu'un seek est impossible.
DFS_READABLE :  Fichier permettant de lire
DFS_WRITABLE :  Fichier permettant d'�crire
DFS_NEWFILE :   Nouveau fichier. Ne peut �tre pr�sent que si DFS_WRITABLE est pr�sent
*/
// Un fichier DFS_STREAM est soit DFS_READABLE soit DFS_WRITABLE | DFS_NEWFILE



void DfsGetSize(DFSFILEWRAP dfsFileWrap,dfuLong32 *posLow, dfuLong32 *posHigh,H_ERROR_INFO* pei);
/*
Retourne la taille d'un fichier DFS.
Param�tres :
DfsFileWrap :   Handle du fichier DFS
Valeur de retour : Taille du fichier DFS en octets

Un fichier avec le flag DFS_STREAM retournera DFS_ERROR_BADPARAMETER
*/

dfuLong32 DfsSeek(DFSFILEWRAP dfsFileWrap, dfuLong32 posLow, dfuLong32 posHigh,H_ERROR_INFO* pei);
dfuLong32 DfsSeekMulAlign(DFSFILEWRAP dfsFileWrap, dfuLong32 posLow, dfuLong32 posHigh,H_ERROR_INFO* pei);
/*
Positionne le pointeur courant dans le fichier DFS (� partir du d�but du fichier).
Param�tres :
DfsFileWrap :   Handle du fichier DFS
Valeur de retour : 0 en cas de succ�s (DFS_SUCCESS)

Un fichier avec le flag DFS_STREAM retournera DFS_ERROR_BADPARAMETER
*/

dfuLong32 DfsRead(DFSFILEWRAP dfsFileWrap, void *Buf,
                  dfuLong32 Size, dfuLong32 * errorCode,H_ERROR_INFO* pei);
/*
Effectue une lecture dans le fichier .DFS
Param�tres :
DfsFileWrap :   Handle du fichier DFS
Buf :   Pointeur vers le buffer recevant les donn�es
Size :  Nombre d'octet � lire
errorCode : Pointeur vers une variable recevant le code d'erreur (peut �tre NULL)
Valeur de retour : Nombre d'octets lus.

Un fichier sans le flag DFS_READABLE retournera 0 et *errorCode � DFS_ERROR_BADPARAMETER
Si le fichier est termin�, *errorcode est � DFS_ERROR_EOF, sinon 0
Avec Size = 0, on peut utiliser cette fonction pour savoir si la fin du fichier est atteinte.
*/

dfuLong32 DfsWrite(DFSFILEWRAP dfsFileWrap, const void *Buf,
                   dfuLong32 Size, dfuLong32 * errorCode,H_ERROR_INFO* pei);
/*
Effectue une �criture dans le fichier .DFS
Param�tres :
DfsFileWrap :   Handle du fichier DFS
Buf :   Pointeur vers le buffer contenant les donn�es
Size :  Nombre d'octet � lire
errorCode : Pointeur vers une variable recevant le code d'erreur (peut �tre NULL)
Valeur de retour : Nombre d'octets �crits.

Un fichier sans le flag DFS_WRITABLE retournera 0 et *errorCode � DFS_ERROR_BADPARAMETER
*/

void DfsTell(DFSFILEWRAP dfsFileWrap, dfuLong32 *posLow, dfuLong32* posHigh, dfuLong32 * errorCode,H_ERROR_INFO* pei);
/* Donne la position courante dans le fichier */

void DfsTellDivAlign(DFSFILEWRAP dfsFileWrap, dfuLong32 *posLow, dfuLong32* posHigh, dfuLong32 * errorCode,H_ERROR_INFO* pei);
/* Donne la position courante dans le fichier */

void DfsMarkEndNow(DFSFILEWRAP dfsFileWrap, dfuLong32 * errorCode,H_ERROR_INFO* pei);
/* Marque la position actuelle comme fin du fichier */

dfuLong32 DfsReadOrWriteFillAlign(DFSFILEWRAP dfsFileWrap, BOOL fWrite,
                                dfuLong32 * errorCode,H_ERROR_INFO* pei);
/* Aligne la position courante dans le fichier (en �crivant des z�ro si neccessaire) */
