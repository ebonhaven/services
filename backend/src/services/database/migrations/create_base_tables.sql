CREATE SCHEMA IF NOT EXISTS "ebonhaven";

CREATE TABLE IF NOT EXISTS "ebonhaven"."accounts" (
  "id" SERIAL PRIMARY KEY,
  "user" TEXT NOT NULL,
  "balance" TEXT NOT NULL,
  "characters" INTEGER[],
  "inventory" INTEGER[]
);

CREATE TABLE IF NOT EXISTS "ebonhaven"."characters" (
  "id" SERIAL PRIMARY KEY,
  "character_id" INTEGER,
  "gender" INTEGER NOT NULL,
  "profession" INTEGER NOT NULL,
  "race" INTEGER NOT NULL,
  "level" INTEGER NOT NULL DEFAULT 1,
  "experience" INTEGER NOT NULL DEFAULT 0,
  "position" JSON DEFAULT '{"world": 0, "zone": 0, "x": 0, "y": 0, "orientation": 0}',
  "in_combat" INTEGER NOT NULL DEFAULT 0,
  "hp" INTEGER NOT NULL DEFAULT 0,
  "max_hp" INTEGER NOT NULL DEFAULT 0,
  "stats" JSON DEFAULT '{"stamina":0, "regen":0, "perception":0, "skill": 0, "luck":0}',
  "attack" JSON DEFAULT '{"physical":0, "spell":0}',
  "defense" JSON DEFAULT '{"physical":0, "spell":0}',
  "equipment" JSON DEFAULT '{"head":"","neck":"","shoulders":"","chest":"","bracers":"","hands":"","legs":"","feet":"","mainhand":"","offhand":"","ranged":"","ring1":"","ring2":"","trinket1":"","trinket2":""}'
)