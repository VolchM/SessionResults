using System;
using System.Collections.Generic;
using System.Linq;
using System.Text.Json.Nodes;

namespace SessionResultsCS
{
    public static class JsonConvert
    {
        public static JsonNode DisciplineToJson(Discipline discipline)
        {
            return new JsonObject
            {
                ["Name"] = discipline.Name,
                ["AttestationType"] = (int)discipline.AttestationType,
            };
        }

        public static JsonNode DisciplineListToJson(DisciplineList disciplineList)
        {
            return new JsonArray(disciplineList.Select(x => DisciplineToJson(x)).ToArray());
        }

        public static JsonNode SessionResultsToJson(SessionResults sessionResults)
        {
            return new JsonObject
            {
                ["Disciplines"] = new JsonArray(sessionResults.GetDisciplines().Select(x => DisciplineToJson(x)).ToArray()),
                ["Results"] = new JsonArray(
                    sessionResults.GetDisciplines().Select(discipline =>
                    {
                        return discipline.AttestationType switch {
                            AttestationType.Exam => sessionResults.GetResult(discipline).ToScore(),
                            AttestationType.PassFailExam => sessionResults.GetResult(discipline).IsPassed() ? 1 : 0,
                        };
                    })
                    .Select(x => JsonValue.Create(x))
                    .ToArray()
                ),
            };
        }

        public static JsonNode StudentToJson(Student student)
        {
            return new JsonObject
            {
                ["StudentID"] = student.StudentID,
                ["FirstName"] = student.FirstName,
                ["LastName"] = student.LastName,
                ["MiddleName"] = student.MiddleName,
                ["SessionResults"] = SessionResultsToJson(student.SessionResults),
            };
        }

        public static JsonNode GroupToJson(Group group)
        {
            return new JsonObject
            {
                ["Name"] = group.Name,
                ["Course"] = group.Course,
                ["Students"] = new JsonArray(group.GetStudents().Select(x => StudentToJson(x)).ToArray()),
            };
        }

        public static JsonNode SpecialityToJson(Speciality speciality)
        {
            return new JsonObject
            {
                ["Code"] = speciality.Code,
                ["Name"] = speciality.Name,
                ["Groups"] = new JsonArray(speciality.GetGroups().Select(x => GroupToJson(x)).ToArray()),
                ["Disciplines"] = new JsonArray(
                    Enumerable.Range(Speciality.MIN_COURSE, Speciality.MAX_COURSE - Speciality.MIN_COURSE + 1)
                        .Select(course => DisciplineListToJson(speciality.GetDisciplineList(course)))
                        .ToArray()
                ),
            };
        }

        public static JsonNode FacultyToJson(Faculty faculty)
        {
            return new JsonObject
            {
                ["Name"] = faculty.Name,
                ["Specialities"] = new JsonArray(faculty.GetSpecialities().Select(x => SpecialityToJson(x)).ToArray())
            };
        }



        public static Discipline DisciplineFromJson(JsonNode json)
        {
            return new Discipline(
                (string)json["Name"],
                (AttestationType)(int)json["AttestationType"]
            );
        }

        public static DisciplineList DisciplineListFromJson(JsonNode json)
        {
            return new DisciplineList(json.AsArray().Select(x => DisciplineFromJson(x)));
        }

        public static SessionResults SessionResultsFromJson(JsonNode json)
        {
            SessionResults sessionResults = new SessionResults();

            foreach (var (discipline, result) in Enumerable.Zip(
                json["Disciplines"].AsArray().Select(x => DisciplineFromJson(x)),
                json["Results"].AsArray().Select(x => (int)x)
            ))
            {
                switch (discipline.AttestationType)
                {
                    case AttestationType.Exam:
                        sessionResults.SetResult(discipline, new ExamResult(result));
                        break;
                    case AttestationType.PassFailExam:
                        sessionResults.SetResult(discipline, new PassFailExamResult(result != 0));
                        break;
                }
            }
            return sessionResults;
        }

        public static Student StudentFromJson(JsonNode json, Group group)
        {
            Student student = new Student(
                group,
                (uint)json["StudentID"],
                (string)json["FirstName"],
                (string)json["LastName"],
                (string)json["MiddleName"]
            );
            student.SessionResults = SessionResultsFromJson(json["SessionResults"]);
            return student;
        }

        public static Group GroupFromJson(JsonNode json, Speciality speciality)
        {
            Group group = new Group(speciality, (string)json["Name"], (int)json["Course"]);
            foreach (var studentJson in json["Students"].AsArray())
            {
                group.AddStudent(StudentFromJson(studentJson, group));
            }
            return group;
        }

        public static Speciality SpecialityFromJson(JsonNode json, Faculty faculty)
        {
            Speciality speciality = new Speciality(faculty, (string)json["Code"], (string)json["Name"]);
            foreach (var groupJson in json["Groups"].AsArray())
            {
                speciality.AddGroup(GroupFromJson(groupJson, speciality));
            }
            int course = Speciality.MIN_COURSE;
            foreach (var disciplineList in json["Disciplines"].AsArray().Select(x => DisciplineListFromJson(x)))
            {
                speciality.SetDisciplineList(course, disciplineList);
                course++;
            }

            return speciality;

        }

        public static Faculty FacultyFromJson(JsonNode json)
        {
            Faculty faculty = new Faculty((string)json["Name"]);
            foreach (var specialityJson in json["Specialities"].AsArray())
            {
                faculty.AddSpeciality(SpecialityFromJson(specialityJson, faculty));
            }
            return faculty;
        }
    }
}
