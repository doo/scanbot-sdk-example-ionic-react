import { CheckRecognizerResult, HealthInsuranceCardScannerResult, MedicalCertificateScannerResult, MrzScannerResult } from "capacitor-plugin-scanbot-sdk";

export class DataDetectorRepository {
    public static MrzResult: { name: string; value: string; }[] = [];

    public static EHICResult: { name: string; value: string; }[] = [];

    public static CheckResult: { name: string; value: string; }[] = [];

    public static MedicalCertifacteResult: { title: string; items: { key: string; value: string; }[]; }[] = [];

    /** Generate readable data from MRZ results */
    public static GeneratMRZResult = (mrzResult: MrzScannerResult) => {
        var mrzData = [
            { name: 'Successful Recognition', value: mrzResult.recognitionSuccessful ? 'YES' : 'NO' },
            { name: 'Document Type', value: mrzResult.documentType },
            { name: 'Raw MRZ String', value: mrzResult.rawString },
            { name: 'Check digits count', value: mrzResult.checkDigitsCount.toString() },
            { name: 'Valid check digits count', value: mrzResult.validCheckDigitsCount.toString() }
        ];

        this.MrzResult = mrzData;
    }

    /** Generate readable data from check results */
    public static GenerateCheckResult = (result: CheckRecognizerResult) => {
        const newFields: { name: any, value: any }[] = []
        result.check.fields.map(item => {
            if (item.value === null || item.value.text === "" || item.value.text === null) return;

            newFields.push({
                name: item.type.name,
                value: item.value?.text
            });
        });
        this.CheckResult = newFields;
    }

    /** Generate readable data from ehic results */
    public static GeneratEHICResult = (result: HealthInsuranceCardScannerResult) => {
        const newFields: { name: string, value: string }[] = []
        result.fields.map(item => {
            newFields.push({
                name: item.type,
                value: item.value
            });
        });
        DataDetectorRepository.EHICResult = newFields;
    }

    /** check the provided object is null */
    private static isObjectEmpty = (objectName: any) => {
        return (
            objectName &&
            Object.keys(objectName).length === 0 &&
            objectName.constructor === Object
        );
    };

    /** Arrange med data to a readable format */
    public static GenerateMedData = async (medData: MedicalCertificateScannerResult) => {
        try {
            this.MedicalCertifacteResult = [];
            if (medData === undefined || medData === null) {
                return;
            }

            if (!this.isObjectEmpty(medData.formType)) {
                this.MedicalCertifacteResult.push(
                    {
                        title: 'General Information',
                        items: [
                            { key: 'FormType', value: medData.formType },
                            { key: 'Captured Image', value: medData.imageFileUri! }
                        ]
                    }
                )
            }
            if (!this.isObjectEmpty(medData.patientData)) {
                this.MedicalCertifacteResult.push(
                    {
                        title: 'Patient Data',
                        items: [
                            { key: 'Insuarance Provider', value: medData.patientData.insuranceProvider?.value! ?? "Not Provided" },
                            { key: 'Full Name', value: (medData.patientData.firstName?.value! + medData.patientData.lastName?.value!) ?? "Not Provided" },
                            { key: 'Address', value: (medData.patientData.address1?.value! + medData.patientData.address2?.value!) ?? "Not Provided" },
                            { key: 'Diagnose', value: medData.patientData.diagnose?.value! ?? "Not Provided" },
                            { key: 'Doctor Number', value: medData.patientData.doctorNumber?.value! ?? "Not Provided" },
                            { key: 'Health Insurance Number', value: medData.patientData.healthInsuranceNumber?.value! ?? "Not Provided" },
                            { key: 'Insured Person Number', value: medData.patientData.insuredPersonNumber?.value! ?? "Not Provided" },
                            { key: 'Place Of Operation Number', value: medData.patientData.placeOfOperationNumber?.value! ?? "Not Provided" },
                        ]
                    }
                )
            }
            if (!this.isObjectEmpty(medData.dates)) {
                this.MedicalCertifacteResult.push(
                    {
                        title: 'Dates',
                        items: [
                            { key: 'Date of Birth', value: medData.dates.birthDate?.dateString! ?? "Not Provided" },
                            { key: 'Diagnose On', value: medData.dates.diagnosedOn?.dateString! ?? "Not Provided" },
                            { key: 'Document Date', value: medData.dates.documentDate?.dateString! ?? "Not Provided" },
                            { key: 'Incapable of work since', value: medData.dates.incapableOfWorkSince?.dateString! ?? "Not Provided" },
                            { key: 'Incapable of work until', value: medData.dates.incapableOfWorkUntil?.dateString! ?? "Not Provided" },
                            { key: 'Child Needs Care From', value: medData.dates.childNeedsCareFrom?.dateString! ?? "Not Provided" },
                            { key: 'Child Needs Care Until', value: medData.dates.childNeedsCareUntil?.dateString! ?? "Not Provided" },
                        ]
                    }
                )
            }
            if (!this.isObjectEmpty(medData.checkboxes)) {
                this.MedicalCertifacteResult.push(
                    {
                        title: 'CheckBoxes',
                        items: [
                            { key: 'Accident Number', value: medData.checkboxes.accidentNo?.isChecked ? 'True' : 'False' },
                            { key: 'Accident', value: medData.checkboxes.accidentNo?.isChecked ? 'True' : 'False' },
                            { key: 'Assigned to Doctor', value: medData.checkboxes.assignedToAccidentInsuranceDoctor?.isChecked ? 'True' : 'False' },
                            { key: 'Work Accident', value: medData.checkboxes.workAccident?.isChecked ? 'True' : 'False' },
                            { key: 'Insured Pay Case', value: medData.checkboxes.insuredPayCase?.isChecked ? 'True' : 'False' },
                            { key: 'Final Certificate', value: medData.checkboxes.finalCertificate?.isChecked ? 'True' : 'False' },
                            { key: 'Initial Certificate', value: medData.checkboxes.initialCertificate?.isChecked ? 'True' : 'False' },
                            { key: 'Other Accident', value: medData.checkboxes.otherAccident?.isChecked ? 'True' : 'False' },
                            { key: 'Renewed Certificate', value: medData.checkboxes.renewedCertificate?.isChecked ? 'True' : 'False' },
                            { key: 'Requires Care No', value: medData.checkboxes.requiresCareNo?.isChecked ? 'True' : 'False' },
                        ]
                    }
                )
            }
        } catch (error) {
            console.log('Medicle certificate data mapping error.');
        }

    }
}
