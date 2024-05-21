The player is presented with the current status of the playing board, where the content of all fields is initially
unknown. The player is given the option to either reveal a field or to mark or unmark a field as likely occupied
by a goose, by asking the player whether to reveal or mark/unmark a field and the two coordinates of the
field.
If the player selects to reveal a field, there are two possible outcomes: (1) the field contains a goose, and the
player upsets the mighty goose. The game is lost immediately. (2) the field does not contain a goose; the field
is revealed. If the field and none of its neighbors contain a goose, the neighboring fields are also revealed,
and the player learns how many geese are in the neighbors of each of the neighboring fields. This value can
range from 0 to 8.
If the player selects to mark or unmark a field, the status of the field is changed from unknown to marked or
from marked to unknown, depending on the current status of the field. Only unknown fields can be revealed
or marked and only marked fields can be unmarked and thereby changed to an unknown field again.
The current status of the board is printed after every change to the fields. The player is free at any turn to
choose to restart with a new game or to quit.
