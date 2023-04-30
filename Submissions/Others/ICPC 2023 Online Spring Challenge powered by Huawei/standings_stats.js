const { readFileSync, writeFileSync } = require('fs');

const preliminary_data = JSON.parse(readFileSync('./preliminary_standings.json')).result.rows.map(({ party: { members: { 0: { handle } } }, rank, points }) => ({ handle, rank, points }));

const final_data = JSON.parse(readFileSync('./final_standings.json')).result.rows.map(({ party: { members: { 0: { handle } } }, rank, points }) => ({ handle, rank, points }));

const handle_preliminary_rank = {};
preliminary_data.forEach(({handle, rank, points}) => {
  handle_preliminary_rank[handle] = rank;
});

const handle_final_rank = {};
final_data.forEach(({handle, rank, points}) => {
  handle_final_rank[handle] = rank;
});

const preliminary_result = [];
preliminary_data.forEach(({handle, rank, points}) => {
  preliminary_result.push({handle, rank, points, delta: rank - handle_final_rank[handle]});
});

const final_result = [];
final_data.forEach(({handle, rank, points}) => {
  final_result.push({handle, rank, points, delta: handle_preliminary_rank[handle] - rank});
});

const get_result_string = (result, preliminary) => {
  let result_string = "";
  result.forEach(({handle, rank, points, delta}) => {
    result_string += `${handle} | ${rank} | ${preliminary ? rank - delta : rank + delta} | ${delta > 0 ? '+' : ''}${delta} |\n`;
  });
  return result_string;
};

const preliminary_result_string = `Handle  | Preliminary Rank | Final Rank | Delta |\n------- | :--------------: | :--------------: | ----: |\n${get_result_string(preliminary_result.slice(0, 200), true)}`.replace(/_/g, '\\_');
const final_result_string = `Handle  | Final Rank | Preliminary Rank | Delta |\n------- | :--------------: | :--------------: | ----: |\n${get_result_string(final_result.slice(0, 200), false)}`.replace(/_/g, '\\_');

writeFileSync('./preliminary_results.txt', preliminary_result_string);
writeFileSync('./final_results.txt', final_result_string);
