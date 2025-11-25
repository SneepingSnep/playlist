#include "../headers/singly_linked_list.h"
#include <dirent.h>
#include <fcntl.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#define TRACK_TITLE_SIZE 60

#define PLAYLIST_IN_PATH "playlist.txt"
#define PLAYLIST_OUT_PATH "playlist-out.txt"
// To avoid unnecessary complexity, we fix the filenames instead of getting them
// through runtime parameters.
char *txtFileIdentifier = "in.txt";
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

    // Here the memcpy is used to cpy the string into a buffer.
    memcpy(data, line, TRACK_TITLE_SIZE);
    printf("About to insert first node...\n");
    // here the node is inserted
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

int main() {

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
  return 0;
}