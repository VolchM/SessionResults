using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace SessionResultsCS.UI
{
    public class DisciplineListPage : LoopPage
    {
        private Speciality _speciality;
        private int _course;

        private DisciplineList _disciplineList;
        private MenuActionPicker _picker;


        public DisciplineListPage(Speciality speciality, int course)
        {
            _speciality = speciality;
            _course = course;
            _disciplineList = speciality.GetDisciplineList(_course);
            _picker = new MenuActionPicker([
                ("Изменить название дисциплины", ChangeDisciplineName),
                ("Добавить дисциплину", AddDiscipline),
                ("Удалить дисциплину", DeleteDiscipline),
                ("Назад", StopLoop),
            ]);
        }

        protected override void Loop()
        {
            Console.WriteLine($"==== Дисциплины - {_course} курс ====");
            PrintDisciplines();
            Console.WriteLine("Действия:");
            _picker.PickAndRun();
        }


        private void ChangeDisciplineName()
        {
            int selectedIndex = SelectDiscipline();
            if (selectedIndex != -1)
            {
                Discipline oldDiscipline = _disciplineList.GetDisciplineAt(selectedIndex);

                try
                {
                    Console.Write("Введите новое название дисциплины: ");
                    string name = Console.ReadLine()!;

                    Discipline newDiscipline = new Discipline(name, oldDiscipline.AttestationType);

                    _disciplineList.RemoveDiscipline(oldDiscipline);
                    _disciplineList.AddDiscipline(newDiscipline);

                    foreach (Group group in _speciality.GetGroups().Where(group => group.Course == _course))
                    {
                        foreach (Student student in group.GetStudents())
                        {
                            AttestationResult? result = student.SessionResults.GetResult(oldDiscipline);
                            if (result != null)
                            {
                                student.SessionResults.DeleteResult(oldDiscipline);
                                student.SessionResults.SetResult(newDiscipline, result);
                            }
                        } 
                    }
                }
                catch (ArgumentException)
                {
                    Console.WriteLine("Не удалось изменить дисциплину");
                }
            }
        }

        private void AddDiscipline()
        {
            Console.Write("Введите название новой дисциплины: ");
            string name = Console.ReadLine()!;
            Console.WriteLine("Выберите тип аттестации новой дисциплины: ");
            AttestationType attestationType = PickAttestationType();

            try
            {
                Discipline discipline = new Discipline(name, attestationType);
                _disciplineList.AddDiscipline(discipline);
            }
            catch (ArgumentException)
            {
                Console.WriteLine("Не удалось добавить дисциплину");
            }
        }

        private void DeleteDiscipline()
        {
            int selectedIndex = SelectDiscipline();
            if (selectedIndex != -1)
            {
                Discipline deletedDiscipline = _disciplineList.GetDisciplineAt(selectedIndex);

                foreach (Group group in _speciality.GetGroups().Where(group => group.Course == _course))
                {
                    foreach (Student student in group.GetStudents())
                    {
                        student.SessionResults.DeleteResult(deletedDiscipline);
                    }
                }

                _disciplineList.RemoveDisciplineAt(selectedIndex);
            }
        }


        private void PrintDisciplines()
        {
            foreach (var (index, discipline) in _disciplineList.Index())
            {
                Console.WriteLine($"{index + 1}. {discipline}");
            }
        }

        private AttestationType PickAttestationType()
        {
            QuickItemPicker attestationTypePicker = new QuickItemPicker(["Экзамен", "Зачёт"]);
            int selected = attestationTypePicker.Pick();
            switch (selected)
            {
                case 0: return AttestationType.Exam;
                case 1: return AttestationType.PassFailExam;
                default: return AttestationType.Exam;
            }
        }

        private int SelectDiscipline()
        {
            Console.Write("Введите номер дисциплины: ");
            string input = Console.ReadLine()!;
            if (int.TryParse(input, out int value) && (value >= 1 && value <= _disciplineList.GetSize()))
            {
                return value - 1;
            }
            else
            {
                Console.WriteLine("Введён неверный номер");
                return -1;
            }
        }
    }
}
