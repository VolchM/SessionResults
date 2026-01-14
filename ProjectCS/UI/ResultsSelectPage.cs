using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace SessionResultsCS.UI
{
    public class ResultsSelectPage: IPage
    {
        private Faculty _faculty;


        public ResultsSelectPage(Faculty faculty)
        {
            _faculty = faculty;
        }

        public void Start()
        {
            if (_faculty.GetSpecialities().All(speciality => speciality.GetGroupCount() == 0))
            {
                Console.WriteLine("В факультете отсутствуют группы");
                return;
            }

            Console.WriteLine("Выберите специальность: ");
            ItemPicker specialityPicker = new ItemPicker(_faculty.GetSpecialities().Select(x => x.ToString()));
            Speciality speciality = _faculty.GetSpecialityAt(specialityPicker.Pick());

            Console.WriteLine("Выберите группу: ");
            ItemPicker groupPicker = new ItemPicker(speciality.GetGroups().Select(x => x.ToString()));
            Group group = speciality.GetGroupAt(groupPicker.Pick());

            Console.WriteLine("Выберите дисциплину: ");
            ItemPicker disciplinePicker = new ItemPicker(group.GetDisciplineList().Select(x => x.ToString()));
            Discipline discipline = group.GetDisciplineList().GetDisciplineAt(disciplinePicker.Pick());

            new ResultsEditingPage(group, discipline).Start();
        }
    }
}
