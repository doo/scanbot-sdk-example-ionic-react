import {
    IonContent,
    IonHeader,
    IonFooter,
    IonPage,
    IonTitle,
    IonToolbar,
    IonBackButton,
    IonButtons,
    IonButton,
    IonImg,
    useIonViewWillEnter,
    IonGrid,
    IonRow,
    IonCol,
} from '@ionic/react';

import { useHistory } from 'react-router';
import React, { useState, useRef } from 'react';

import { ImageResultsRepository } from '../utils/ImageRepository';
import ScanbotService from '../services/scanbot_service';
import CommonModalView from './common_components/CommonModalView';
import { PDFPageSizeList, TiffOptions } from '../utils/data_util';
import { PDFPageSizeEnum } from '../enums/pdf_page_size_enum';
import { ShowAlert } from '../services/alert_service';
import { TiffOptionsEnum } from '../enums/tiff_option_enum';
import { Page, PageSize } from 'capacitor-plugin-scanbot-sdk';

const ImagePreview: React.FC = () => {

    const history = useHistory();
    const initialState = useState<any>([]);
    const [imageData, setImageData] = initialState;

    let pages = useRef<Page[]>([]);
    const pdfModalView = useRef<HTMLIonModalElement>(null);

    useIonViewWillEnter(() => {
        reloadPages();
    });

    function hasScannedPages(): boolean {
        if (!pages || pages.current.length === 0) {
            alert('No scanned images were found. Please scan at least one page.');
            return false;
        }
        return true;
    }

    /* load scanned documents */
    async function reloadPages() {
        if (!(await ScanbotService.validateLicense())) { return; }

        imageData.value = [];
        try {
            pages.current = ImageResultsRepository.INSTANCE.getPages();

            if (!hasScannedPages()) { return; }

            for (const page of pages.current) {
                const url = page.documentPreviewImageFileUri as string;
                const imageURL = await ScanbotService.fetchDataFromUri(url);
                if (imageURL === '' || imageURL === undefined) break;

                setImageData((imageData: any) => [...imageData, { id: page.pageId, url: imageURL }]);
            }
        }
        catch (error) {
            console.error(error);
        }
    }

    /* Navigate to cropping page */
    function navigateToCroppingPage(pageId: string): void {
        history.push("/imageeditview/" + pageId);
        setImageData(() => initialState)
    }

    /* Scan Document */
    const startDocumentScanner = async () => {
        if (!(await ScanbotService.validateLicense())) { return; }

        try {
            const documentResult = await ScanbotService.startDocumentScanner();

            if (documentResult!.status == 'CANCELED') {
                await ShowAlert('Information', 'Document scanner has been canceled.', ['OK']);
                return;
            };
            await ImageResultsRepository.INSTANCE.addPages(documentResult!.pages);
            await reloadPages();
        }
        catch (error) {
            await ShowAlert('Scan Document Failed', JSON.stringify(error), ['OK']);
        }
    }

    /* Create PDF from scanned image urls */
    const createPDF = async (selectedItem: PDFPageSizeEnum) => {
        if (!(await ScanbotService.validateLicense())) {
            pdfModalView.current?.dismiss();
            return;
        }

        try {
            const imageUrls = pages.current.map(p => p.originalImageFileUri!);
            const pdfPageSize = PDFPageSizeList[selectedItem].value as PageSize;

            const result = await ScanbotService.createPDF(imageUrls, pdfPageSize);
            alert('start');
            pdfModalView.current?.dismiss();
            alert('end');
            if (result!.status == 'CANCELED') {
                await ShowAlert('Information', 'PDF Creation has been canceled.', ['OK']);
                return;
            };
            alert(JSON.stringify(result));
        }
        catch (error) {
            //pdfPageSizeModal.value.cancel();
            await ShowAlert('PDF Creation Failed', JSON.stringify(error), ['OK']);
        }
    }

    /* Create TIFF from scanned image urls */
    const writeTIFF = async (selectedItem: TiffOptionsEnum) => {
        if (!(await ScanbotService.validateLicense())) {
            //tiffOptionModal.value.cancel();
            return;
        }

        try {
            const imageUrls = pages.current.map(p => p.documentImageFileUri!);
            const binarized = selectedItem === TiffOptionsEnum.Binarized;

            const result = await ScanbotService.writeTIFF(imageUrls, binarized);

            //tiffOptionModal.value.cancel();
            if (result!.status == 'CANCELED') {
                await ShowAlert('Information', 'TIFF Creation has been canceled.', ['OK']);
                return;
            };
            alert(JSON.stringify(result));
        }
        catch (error) {
            //tiffOptionModal.value.cancel();
            await ShowAlert('TIFF Creation Failed', JSON.stringify(error), ['OK']);
        }
    }

    const deleteAll = async () => {
        await ImageResultsRepository.INSTANCE.removeAllPages();
        pages.current = [];
        setImageData([]);
        await ScanbotService.cleanUp();
    }

    return (
        <IonPage>
            <IonHeader>
                <IonToolbar color="primary">
                    <IonButtons slot="start">
                        <IonBackButton />
                    </IonButtons>
                    <IonTitle>Image Preview</IonTitle>
                </IonToolbar>
            </IonHeader>

            <IonContent fullscreen>
                <IonGrid>
                    <IonRow>
                        {imageData.map((page: any) => (
                            <IonCol size="4" key={page.id}>
                                <IonImg onClick={() => navigateToCroppingPage(page.id)} src={page.url} />
                            </IonCol>
                        ))}
                    </IonRow>
                </IonGrid>
            </IonContent>

            <IonFooter>
                <IonToolbar>
                    <IonButtons slot="start">

                        <IonButton onClick={startDocumentScanner}>Add</IonButton>

                        <CommonModalView
                            id='pdf-modal'
                            modalTitle='PDF Page Size Options'
                            buttonTitle='Create PDF'
                            initialBreakPoint={0.5}
                            optionList={PDFPageSizeList}
                            onItemClick={createPDF} />

                        <CommonModalView
                            id='tiff-modal'
                            modalTitle='Tiff Creation Options'
                            buttonTitle='Create TIFF'
                            initialBreakPoint={0.25}
                            optionList={TiffOptions}
                            onItemClick={writeTIFF} />

                    </IonButtons>

                    <IonButtons slot="end">
                        <IonButton onClick={deleteAll}>Delete</IonButton>
                    </IonButtons>
                </IonToolbar>
            </IonFooter>
        </IonPage>
    );
};

export default ImagePreview;