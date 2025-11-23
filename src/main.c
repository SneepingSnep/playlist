#include "../headers/singly_linked_list.h"
#include "raylib.h"
#include <dirent.h>
#include <fcntl.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#define MAX_FILEPATH_SIZE 1024
#define TRACK_TITLE_SIZE 60

#define PLAYLIST_IN_PATH "playlist.txt"
#define PLAYLIST_OUT_PATH "playlist-out.txt"
// To avoid unnecessary complexity, we fix the filenames instead of getting them
// through runtime parameters.
char *txtFileIdentifier = "in.txt";
char inputTxtfiles[3][MAX_FILEPATH_SIZE];
size_t inputTxtFilesentries = 0;
typedef char Data[TRACK_TITLE_SIZE];
Node *playlist;

/// Removes trailing newline from the line, if it exists.
/// Note: Some lines may not have a newline, e.g., last line in a file,
/// therefore we have to check for presence.
char *remove_newline_if_exists(char *line) {
  // YOUR CODE HERE
  char newlineFinder = '\n';
  int lineLength = strlen(line);
  for (size_t lineIndex = 0; lineIndex < lineLength; lineIndex++) {
    if (newlineFinder == line[lineIndex])
      line[lineIndex] = ' ';
  }
  return line;
}

/// Reads lines from at `filename`, creates a node for each line and inserts
/// nodes to `list`.
Node **load_file(const char *filename, Node **list) {
  // Open the file and assign to stream `f`
  // YOUR CODE HERE
  FILE *f = fopen(filename, "r");
  if (!f) {
    perror(PLAYLIST_IN_PATH);
    exit(EXIT_FAILURE);
  }
  char line[TRACK_TITLE_SIZE];
  size_t listcntr = 0;
  while (fgets(line, TRACK_TITLE_SIZE, f)) {
    remove_newline_if_exists(line);

    auto new_node = (Node *)malloc(sizeof(Node));
    new_node->next = nullptr;
    auto data = (Data *)malloc(sizeof(Data));
    new_node->data = data;

    // Copy line to `new_node` and append `new_node` to `list`
    // YOUR CODE HERE
    memcpy(data, line, TRACK_TITLE_SIZE);
    printf("About to insert first node...\n");
    // if (listcntr == 0) {
    //   list = NULL;
    // }
    insert_at(list, list_len(*list), new_node);
  }
  fclose(f);
  return list;
}

/// Saves `list` contents to the file at `filename`.
void save_file(const char *filename, Node *list) {
  // Open file
  // YOUR CODE HERE
  FILE *f = fopen(filename, "w");

  // Move through the list and save the tracks to the file
  // Note: You have to cast the data to print the track to the file as
  // follows:
  // `*(Data *)current->data`, which is the same as `(char *)current->data`.
  // We need this cast, because `data` is a pointer to everything (`void *`).
  auto current = playlist;
  // YOUR CODE HERE
  int playlistNu = 1;
  Node *adress = playlist;
  while (adress) {
    printf("%s\n", (char *)adress->data);
    fprintf(f, "%s\n", *(Data *)adress->data);
    adress = adress->next;
    playlistNu++;
  }
  fclose(f);
}

void print_tracks(const Node *const playlist) {
  auto current = playlist;
  for (size_t i = 1; current; i++, current = current->next)
    printf("%2zu: %s\n", i, (char *)current->data);
}

void findtextfiles(char *dir) {
  // function to find files ending with in.txt
  int txtlen = strlen("in.txt");
  DIR *dp;
  struct dirent *entry;
  struct stat statbuf;
  // opening directory kinda like a file but with another function
  if ((dp = opendir(dir)) == NULL) {
    fprintf(stderr, "cannot open directory: %s\n", dir);
    return;
  }
  // changes directory to actual.
  chdir(dir);
  while ((entry = readdir(dp)) != NULL) {
    // in here i retrieve the name into a buffer and filter the buffername
    // untill i get the values i want
    stat(entry->d_name, &statbuf);
    // filterPointer = strtok(entry->d_name, "-");
    // filterPointer = strtok(NULL, "-");
    int filtervalue = strlen(entry->d_name) - txtlen;
    if ((strcmp(entry->d_name + filtervalue, txtFileIdentifier)) == 0) {
      printf("%s\n", entry->d_name);
      memcpy(inputTxtfiles[inputTxtFilesentries], entry->d_name,
             MAX_FILEPATH_SIZE);
      inputTxtFilesentries++;
    }
  }
  closedir(dp);
}

int main() {

  findtextfiles(
      "C:\\Users\\sebas\\OneDrive\\DTU\\cprog\\Code samples\\playlist");
#if 1
  const int screenWidth = 2000;
  const int screenHeight = 1500;

  InitWindow(screenWidth, screenHeight,
             "raylib [core] example - directory files");

  int btnBackPressed = false;

  SetTargetFPS(60);
  //--------------------------------------------------------------------------------------
  // Main game loop
  while (!WindowShouldClose()) // Detect window close button or ESC key
  {
    // Update
    //----------------------------------------------------------------------------------
    // if (btnBackPressed) {
    //   TextCopy(directory, GetPrevDirectoryPath(directory));
    //   UnloadDirectoryFiles(files);
    //   files = LoadDirectoryFiles(directory);
    // }
    //----------------------------------------------------------------------------------

    // Draw
    //----------------------------------------------------------------------------------
    BeginDrawing();
    ClearBackground(RAYWHITE);

    DrawText("directory", 100, 40, 20, DARKGRAY);

    btnBackPressed = GuiButton((Rectangle){40.0f, 38.0f, 48, 24}, "<");

    // for (int i = 0; i < (int)files.count; i++) {
    Color color = Fade(LIGHTGRAY, 0.3f);

    for (int i = 0; i < 3; i++) {
      GuiButton((Rectangle){0.0f, 85.0f + 40.0f * (float)i,
                            screenWidth / (float)2, 40},
                "");

      DrawRectangle(0, 85 + 40 * i, screenWidth / (float)2, 40, color);
      DrawText(inputTxtfiles[i], 120, 100 + 40 * i, 10, GRAY);
    }

    EndDrawing();
    //----------------------------------------------------------------------------------
  }

  // De-Initialization
  //--------------------------------------------------------------------------------------
  // UnloadDirectoryFiles(files);

  CloseWindow(); // Close window and OpenGL context
  //--------------------------------------------------------------------------------------

  return 0;
  playlist = NULL;
  load_file(PLAYLIST_IN_PATH, &playlist);
  puts("Loaded tracks:");
  print_tracks(playlist);

  // Deletion
  size_t node_index_to_del = 4;
  free(delete_at(&playlist, node_index_to_del));

  // Insertion
  Node node = {.data = "Tarkan – Şımarık 💋", .next = nullptr};
  insert_at(&playlist, 3, &node);

  save_file(PLAYLIST_OUT_PATH, playlist);
#endif
  return 0;
}