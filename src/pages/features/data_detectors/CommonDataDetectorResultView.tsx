import { IonBackButton, IonButtons, IonContent, IonHeader, IonItem, IonLabel, IonList, IonPage, IonTitle, IonToolbar, useIonViewWillEnter } from "@ionic/react";

type Props = {
    title: string,
    dataList: { name: any; value: string; }[],
};

const CommonDataDetectorResultView: React.FC<Props> = (props: Props) => {

    return (
        <IonPage>
            <IonHeader>
                <IonToolbar color="primary">
                    <IonButtons slot="start">
                        <IonBackButton />
                    </IonButtons>
                    <IonTitle>{props.title}</IonTitle>
                </IonToolbar>
            </IonHeader>

            <IonContent fullscreen>
                <IonList>
                    {
                        props.dataList.map((item) => (
                            <IonItem>
                                <IonLabel>
                                    <h3>{item.name}</h3>
                                    <p>{item.value}</p>
                                </IonLabel>
                            </IonItem>
                        ))
                    }
                </IonList>
            </IonContent>
        </IonPage>
    );
}

export default CommonDataDetectorResultView;