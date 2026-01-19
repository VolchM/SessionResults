using System;
using System.Collections.Generic;
using System.Text;

namespace SessionResultsCS.UI
{
    public class MainMenuPage : LoopPage
    {
        private string _fileName;
        private IFacultyStorage _storage;


        public MainMenuPage(string fileName)
        {
            _fileName = fileName;
            _storage = new FacultyJsonStorage(_fileName);
            SetPicker(new MenuActionPicker([
                ("Создание таблицы успеваемости группы и экспорт", GoToGroupTablePage ),
                ("Изменение информации факультета", GoToFacultyPage ),
                ("Изменение результатов аттестации", GoToResultsEditingPage ),
                ("Выбрать файл", SelectFile ),
                ("Создать новый файл", CreateNewFile ),
                ("Выход из программы", StopLoop),
            ]));
        }


        protected override void Loop()
        {
            Console.WriteLine("========== Главное меню ==========");
            Console.WriteLine($"Выбранный файл: {_fileName}");
        }

        private void GoToGroupTablePage()
        {
            Faculty? faculty = TryLoadFaculty();
            if (faculty != null)
            {
                new GroupTablePage(faculty).Start();
            }
        }

        private void GoToFacultyPage()
        {
            Faculty? faculty = TryLoadFaculty();
            if (faculty != null)
            {
                new FacultyPage(faculty).Start();
                TrySaveFaculty(faculty);
            }
        }

        private void GoToResultsEditingPage()
        {
            Faculty? faculty = TryLoadFaculty();
            if (faculty != null)
            {
                new ResultsSelectPage(faculty).Start();
                TrySaveFaculty(faculty);
            }
        }

        private void SelectFile()
        {
            Console.Write("Введите имя файла: ");
            _fileName = Console.ReadLine()!;

            _storage = new FacultyJsonStorage(_fileName);
        }

        private void CreateNewFile()
        {
            Console.Write("Введите имя файла: ");
            _fileName = Console.ReadLine()!;
            _storage = new FacultyJsonStorage(_fileName);

            Console.Write("Введите имя факультета: ");
            string facultyName = Console.ReadLine()!;

            try
            {
                TrySaveFaculty(new Faculty(facultyName));
            }
            catch (ArgumentException)
            {
                Console.WriteLine("Введено некорректное название факультета");
            }
        }

        private Faculty? TryLoadFaculty()
        {
            try
            {
                return _storage.Load();
            }
            catch
            {
                Console.WriteLine("Не удалось загрузить данные факультета из файла");
                return null;
            }
        }

        private void TrySaveFaculty(Faculty faculty)
        {
            try
            {
                _storage.Save(faculty);
            }
            catch (Exception)
            {
                Console.WriteLine("Не удалось сохранить изменения факультета в файл");
            }
        }

    }
}
