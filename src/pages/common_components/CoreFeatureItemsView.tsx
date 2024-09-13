import { IonBackButton, IonButtons, IonContent, IonHeader, IonItem, IonLabel, IonList, IonPage, IonTitle, IonToolbar } from "@ionic/react";
import { CoreFeatureEnum } from "../../enums/core_feature_enum";

type Props = {
    title: string,
    dataList: { key: CoreFeatureEnum; value: string; }[],
    onItemClick: Function
};

const CoreFeatureItemsView: React.FC<Props> = (props: Props) => {
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
                            <IonItem button key={item.key} onClick={() => props.onItemClick(item.key)}>
                                <IonLabel>{item.value}</IonLabel>
                            </IonItem>
                        ))
                    }
                </IonList>
            </IonContent>
        </IonPage>
    );
}

export default CoreFeatureItemsView;